#include "FlashParticle.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Define/Window.h"
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
static constexpr int THREAD_X = 16, THREAD_Y = 16;
static constexpr int DISPATCH_X = 4, DISPATCH_Y = 4;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;
const int NUM = 1;

struct Particle {
    float lifeTime;
    Math::Vector3 position;
    Math::Vector3 velocity;
    Graphics::Color4 color;
};

struct GlobalData {
    float deltaTime;
    UINT emit;
    float d[2];
    Math::Vector3 pos;
    float dummy[1];
};

struct Lerp {
    Math::Vector3 start;
    Math::Vector3 end;

    Math::Vector3 operator()(float t) {
        return start * (1.0f - t) + end * t;
    }
};

std::vector<std::unique_ptr<Graphics::GPUParticle>> mGPUParticle; //!< パーティクル
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! グローバルデータ用コンスタントバッファ
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<Utility::Timer> mTimer;
std::shared_ptr<Graphics::Sprite2D> mSprite;
GlobalData mGlobal;
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mText;
int mNum;
Math::Vector3 mCameraPos, mCameraLookat;
Lerp mLerp;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}
}

FlashParticle::FlashParticle() {    //カメラの初期化
    mCameraPos = Math::Vector3(0, 0, -30);
    mCameraLookat = Math::Vector3(0, 0, 0);
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ mCameraPos,mCameraLookat,Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());

    //アルファブレンドの作成
    mAlphaBlend = createAlphaBlend();

    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance().range(0.0f, 1.0f);
    }

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    auto gs = std::make_shared<Graphics::GeometoryShader>("Particle/Flash_GS");
    auto ps = std::make_shared<Graphics::PixelShader>("Particle/Flash_PS");
    auto vs = std::make_shared<Graphics::VertexShader>("Particle/Flash_VS");

    for (int i = 0; i < NUM; i++) {
        //コンピュートシェーダ作成
        Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
        auto cs = std::make_shared<Graphics::ComputeShader>("Particle/Flash_CS", info);

        //パーティクルのデータ作成
        std::vector<Particle> particle(COUNT);
        for (int i = 0; i < COUNT; i++) {
            particle[i] = Particle{ -1.0f,Math::Vector3::ZERO ,Math::Vector3::ZERO, Graphics::Color4(1.0f,1.0f,1.0f,0.0f) };
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

    mTimer = std::make_unique<Utility::Timer>(0.5f);
    mTimer->init();

    mGlobal.emit = -1;
    mNum = NUM;
    mSprite = std::make_shared<Graphics::Sprite2D>(Utility::ResourceManager::getInstance().getTexture()->getResource(Define::TextureType::Circle));
    mLerp.start = Math::Vector3(50, 10, 0);
    mLerp.end = Math::Vector3(-50, -10, 0);

    mWindow = std::make_unique<ImGUI::Window>("Parameter");
    mText = std::make_shared<ImGUI::Text>("");
    mWindow->addItem(mText);

#define ADD_CHANGE_CENTER_FIELD(name,type,min,max) {\
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name,static_cast<float>(type),[&](float val){\
        type = static_cast<int>(val); \
    }); \
        mWindow->addItem(field); \
        field->setMinValue(min); \
        field->setMaxValue(max); \
    }

    ADD_CHANGE_CENTER_FIELD(N, mNum, 0, NUM);

#define ADD_CAMERA_PARAMETER_CHANGE_FIELD(name,type,min,max) { \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name,type,[&](float val){ \
        type = val; \
    }); \
    mWindow->addItem(field); \
    field->setMinValue(min); \
    field->setMaxValue(max); \
    }

    ADD_CAMERA_PARAMETER_CHANGE_FIELD(CAMERA_X, mCameraPos.x, -30.0f, 30.0f);
    ADD_CAMERA_PARAMETER_CHANGE_FIELD(CAMERA_Y, mCameraPos.y, -30.0f, 30.0f);
    ADD_CAMERA_PARAMETER_CHANGE_FIELD(CAMERA_Z, mCameraPos.z, -30.0f, 30.0f);
    ADD_CAMERA_PARAMETER_CHANGE_FIELD(CAMERA_CX, mCameraLookat.x, -30.0f, 30.0f);
    ADD_CAMERA_PARAMETER_CHANGE_FIELD(CAMERA_CY, mCameraLookat.y, -30.0f, 30.0f);
    ADD_CAMERA_PARAMETER_CHANGE_FIELD(CAMERA_CZ, mCameraLookat.z, -30.0f, 30.0f);
}

FlashParticle::~FlashParticle() {}

void FlashParticle::load(Scene::Collecter& collecter) {
    mTimer->init();
}

void FlashParticle::update() {
    mTimer->update(Utility::Time::getInstance().getDeltaTime());

    mGlobal.deltaTime = Utility::Time::getInstance().getDeltaTime();

    float t = (1.0f - mTimer->getCurrentTime() / mTimer->getLimitTime());
    Math::MathUtility::clamp(t, 0.0f, 1.0f);
    mGlobal.pos = mLerp(t);

    mGlobal.emit = mTimer->isTime() ? -1 : (mGlobal.emit + 1) /*% (THREAD_X * THREAD_Y)*/;
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();
    for (int i = 0; i < mNum; i++) {
        mGPUParticle[i]->simulate();
    }
}

bool FlashParticle::isEndScene() const {
    return false;
}

void FlashParticle::draw(Framework::Graphics::IRenderer* renderer) {
    Utility::getContext()->RSSetState(ras.Get());
    dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->setPosition(mCameraPos);
    m3DCamera->setLookat(mCameraLookat);
    m3DCamera->render();

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(245.0f / 255.0f, 242.0f / 255.0f, 66.0f / 255.0f, 0.1f));
    Math::Matrix4x4 m = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World, m);
    Utility::getConstantBufferManager()->send();

    for (int i = 0; i < mNum; i++) {
        mGPUParticle[i]->draw();
    }

    mText->setText(Utility::StringBuilder("") << mNum * COUNT);
    mWindow->draw();
}

void FlashParticle::end() {}

Define::SceneType FlashParticle::next() {
    return Define::SceneType();
}
