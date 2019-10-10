#include "ShotParticle.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Utility/Time.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Graphics/Particle/GPUParticle.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Collision.h"
#include "Framework/Utility/Random.h"

using namespace Framework;

namespace {
static constexpr int THREAD_X = 16, THREAD_Y = 16;
static constexpr int DISPATCH_X = 1, DISPATCH_Y = 1;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;
const int NUM = 256;

struct Particle {
    float lifeTime;
    Math::Vector3 position;
    Math::Vector3 velocity;
    Graphics::Color4 color;
};

struct GlobalData {
    float deltaTime;
    float dummy[3];
};

struct OnceShotDataBuffer {
    UINT emitIndex;
    Math::Vector3 emitPosition;
};

struct OnceShotData {
    UINT index;
    Math::Vector3 start;
    Math::Vector3 end;
    Utility::Timer timer;
};

std::vector<std::pair<OnceShotData, std::unique_ptr<Graphics::GPUParticle>>> mGPUParticle; //!< パーティクル
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! グローバルデータ用コンスタントバッファ
std::unique_ptr<Graphics::ConstantBuffer<OnceShotDataBuffer>> mShotCB; //<! グローバルデータ用コンスタントバッファ
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mText;
GlobalData mGlobal;
int mCurrentShotNum;
std::unique_ptr<Utility::Timer> mTimer;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}
}

ShotParticle::ShotParticle() {    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0, 10, -10),Math::Vector3(0, 0, 0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());

    //アルファブレンドの作成
    mAlphaBlend = createAlphaBlend();

    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance()->range(0.0f, 1.0f);
    }

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    mShotCB = std::make_unique<Graphics::ConstantBuffer<OnceShotDataBuffer>>(Graphics::ShaderInputType::Compute, 1);
    auto gs = std::make_shared<Graphics::GeometoryShader>("Particle/Flash_GS");
    auto ps = std::make_shared<Graphics::PixelShader>("Particle/Flash_PS");
    auto vs = std::make_shared<Graphics::VertexShader>("Particle/Flash_VS");

    Utility::ResourceManager::getInstance()->getVertexShader()->getResource(Define::VertexShaderType::Model);

    for (int i = 0; i < NUM; i++) {
        //コンピュートシェーダ作成
        Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
        auto cs = std::make_shared<Graphics::ComputeShader>("Particle/ShotParticle_CS", info);

        //パーティクルのデータ作成
        std::vector<Particle> particle(COUNT);
        for (int i = 0; i < COUNT; i++) {
            particle[i] = Particle{ -1.0f,Math::Vector3::ZERO ,Math::Vector3::ZERO, Graphics::Color4(1.0f,1.0f,1.0f,0.0f) };
        }
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        cs->addSRV(0, randomTable);
        std::vector<int> randomSeed{ Utility::Random::getInstance()->range(0,RANDOM_MAX) };

        cs->addUAV(0, randomSeed);

        mGPUParticle.emplace_back(OnceShotData{ INT_MAX,Math::Vector3::ZERO,Math::Vector3::ZERO,Utility::Timer(0.0f) },
            std::make_unique<Graphics::GPUParticle>(COUNT,
                Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Circle),
                cs,
                vs,
                ps,
                gs));
    }


    //ラスタライザ作成
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Graphics::DX11InterfaceAccessor::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());

    mCurrentShotNum = 0;
    mGlobal.deltaTime = 0.0f;
    mTimer = std::make_unique<Utility::Timer>(0.1f);

    mWindow = std::make_unique<ImGUI::Window>("Parameter");
    mText = std::make_shared<ImGUI::Text>("");
    mWindow->addItem(mText);
}

ShotParticle::~ShotParticle() {}

void ShotParticle::load(Scene::Collecter& collecter) {}

void ShotParticle::update() {
    mTimer->update(Utility::Time::getInstance()->getDeltaTime());
    if (mTimer->isTime()) {
        mTimer->init();
        const float x = Utility::Random::getInstance()->range(0.0f, 30.0f);
        const float y = 10.0f;
        const float z = Utility::Random::getInstance()->range(0.0f, 10.0f);
        Math::Vector3 n = Math::Vector3(x, y, z);
        Math::Vector3 f = n + Math::Vector3(-30, -20, 0);
        mGPUParticle[mCurrentShotNum].first.start = n;
        mGPUParticle[mCurrentShotNum].first.end = f;
        mGPUParticle[mCurrentShotNum].first.timer = Utility::Timer(1.0f);
        mGPUParticle[mCurrentShotNum].first.index = 0;
        mCurrentShotNum = (mCurrentShotNum + 1) % mGPUParticle.size();
    }

    mGlobal.deltaTime = Utility::Time::getInstance()->getDeltaTime();

    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();

    auto lerp = [](const Math::Vector3& v1, const Math::Vector3& v2, float t) {
        return v1 * (1.0f - t) + v2 * t;
    };

    for (int i = 0; i < mGPUParticle.size(); i++) {
        if (mGPUParticle[i].first.index == INT_MAX)continue;
        OnceShotDataBuffer buf;
        buf.emitIndex = mGPUParticle[i].first.timer.isTime() ? -1 : mGPUParticle[i].first.index;
        mGPUParticle[i].first.index++;
        mGPUParticle[i].first.timer.update(Utility::Time::getInstance()->getDeltaTime());
        Math::Vector3 s = mGPUParticle[i].first.start;
        Math::Vector3 e = mGPUParticle[i].first.end;
        float t = 1.0f - (mGPUParticle[i].first.timer.getCurrentTime() / mGPUParticle[i].first.timer.getLimitTime());
        Math::MathUtility::clamp(t, 0.0f, 1.0f);
        buf.emitPosition = lerp(s, e, t);
        mShotCB->setBuffer(buf);
        mShotCB->sendBuffer();
        mGPUParticle[i].second->simulate();
    }
}

bool ShotParticle::isEndScene() const {
    return false;
}

void ShotParticle::draw(Framework::Graphics::IRenderer* renderer) {
    //Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    //dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    //renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    //mAlphaBlend->set();
    //Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    //Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    //Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    //Math::Matrix4x4 m = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    //Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    //Utility::getConstantBufferManager()->send();

    //for (int i = 0; i < mGPUParticle.size(); i++) {
    //    mGPUParticle[i].second->draw();
    //}

    //mText->setText(Utility::StringBuilder("") << mGPUParticle.size() * COUNT);
    //mWindow->draw();
}

void ShotParticle::end() {}

Define::SceneType ShotParticle::next() {
    return Define::SceneType();
}
