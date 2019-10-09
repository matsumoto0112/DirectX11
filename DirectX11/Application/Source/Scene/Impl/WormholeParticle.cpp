#include "WormholeParticle.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Wrap/DirectX.h"
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
#include "Framework/Utility/Random.h"

using namespace Framework;

namespace {
static constexpr int THREAD_X = 32, THREAD_Y = 32;
static constexpr int DISPATCH_X = 1, DISPATCH_Y = 1;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;
constexpr int NUM = 64;

struct Particle {
    float lifeTime;
    float speed;
    Math::Vector3 position;
    Math::Vector3 velocity;
    Graphics::Color4 color;
};

struct GlobalData {
    float deltaTime;
    float dummy[3];
};

struct ParticleParameter {
    UINT index;
    Math::Vector3 spot;
    Math::Vector3 center;
    float radius;
};

std::vector<std::unique_ptr<Graphics::GPUParticle>> mGPUParticle; //!< パーティクル
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! グローバルデータ用コンスタントバッファ
std::unique_ptr<Graphics::ConstantBuffer<ParticleParameter>> mParameterCB; //<! パラメータ用コンスタントバッファ
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
GlobalData mGlobal;
ParticleParameter mParameter;
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mText;
int mNum;
float mSpeed;
float mMaxYPosition;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}
}

WormholeParticle::WormholeParticle() {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0, 30, -30),Math::Vector3(0, 0, 0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance().getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Config::getInstance().getSize());

    //アルファブレンドの作成
    mAlphaBlend = createAlphaBlend();

    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance().range(0.0f, 1.0f);
    }

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    mParameterCB = std::make_unique<Graphics::ConstantBuffer<ParticleParameter>>(Graphics::ShaderInputType::Compute, 1);
    auto gs = Utility::ResourceManager::getInstance().getGeometoryShader()->getResource(Define::GeometoryShader::SpotInstancer);
    auto ps = Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::CubeParticle);
    auto vs = Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Wormhole);

    for (int i = 0; i < NUM; i++) {
        //コンピュートシェーダ作成
        Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
        auto cs = std::make_shared<Graphics::ComputeShader>("Particle/Wormhole_CS", info);

        //パーティクルのデータ作成
        std::vector<Particle> particle(COUNT);
        for (int i = 0; i < COUNT; i++) {
            particle[i] = Particle{ -1.0f,0.0f ,Math::Vector3::ZERO,Math::Vector3::ZERO, Graphics::Color4(1.0f,1.0f,1.0f,0.0f) };
        }
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        cs->addSRV(0, randomTable);
        std::vector<int> randomSeed{ Utility::Random::getInstance().range(0,RANDOM_MAX) };

        cs->addUAV(0, randomSeed);

        mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(COUNT,
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
    Utility::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Utility::getContext()->RSSetState(ras.Get());

    mSpeed = 30.0f;
    mParameter.index = -1;
    mParameter.spot = Math::Vector3::ZERO;
    mParameter.radius = 10.0f;
    mNum = NUM;
    mMaxYPosition = 20.0f;

    mWindow = std::make_unique<ImGUI::Window>("Parameter");
    mText = std::make_shared<ImGUI::Text>("");
    mWindow->addItem(mText);

#define ADD_CHANGE_FIELD(name,var,min,max) { \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name,var,[&](float val){var = val;}); \
    mWindow->addItem(field); \
    field->setMinValue(min); \
    field->setMaxValue(max); \
    }

    ADD_CHANGE_FIELD(RADIUS, mParameter.radius, 0.0f, 30.0f);
    ADD_CHANGE_FIELD(SPEED, mSpeed, 0.0f, 100.0f);
    ADD_CHANGE_FIELD(MAX_Y, mMaxYPosition, 0.0f, 100.0f);
}

WormholeParticle::~WormholeParticle() { }

void WormholeParticle::load(Scene::Collecter& collecter) {
}

void WormholeParticle::update() {
    mGlobal.deltaTime = Utility::Time::getInstance().getDeltaTime();
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();

    mParameter.index = (mParameter.index + 1) % (THREAD_X * THREAD_Y);

    mParameter.spot.y += 1.0f * mSpeed *  Utility::Time::getInstance().getDeltaTime();
    if (mParameter.spot.y > mMaxYPosition)mParameter.spot.y -= Math::MathUtility::abs(mMaxYPosition) * 2;
    mParameter.center = mParameter.spot + Math::Vector3(0, -10, 0);
    mParameterCB->setBuffer(mParameter);
    mParameterCB->sendBuffer();

    for (int i = 0; i < mNum; i++) {
        mGPUParticle[i]->simulate();
    }
}

bool WormholeParticle::isEndScene() const {
    return false;
}

void WormholeParticle::draw(Framework::Graphics::IRenderer* renderer) {
    Utility::getContext()->RSSetState(ras.Get());
    dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Matrix4x4 m = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World, m);
    Utility::getConstantBufferManager()->send();

    for (int i = 0; i < mNum; i++) {
        mGPUParticle[i]->draw();
    }

    mText->setText(Utility::StringBuilder("") << mNum * COUNT);
    mWindow->draw();
}

void WormholeParticle::end() { }

Define::SceneType WormholeParticle::next() {
    return Define::SceneType();
}
