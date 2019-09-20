#include "SpotInstancerParticle.h"
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
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Graphics/Particle/GPUParticle.h"

using namespace Framework;

namespace {
static constexpr int THREAD_X = 32, THREAD_Y = 32;
static constexpr int DISPATCH_X = 1, DISPATCH_Y = 1;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;
const int NUM = 1;

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

struct EmitParameter {
    UINT emitTargetIndex;
    Math::Vector3 spot;
    Math::Vector3 center;
    float dummy[1];
};

std::vector<std::unique_ptr<Graphics::GPUParticle>> mGPUParticle; //!< パーティクル
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! グローバルデータ用コンスタントバッファ
std::unique_ptr<Graphics::ConstantBuffer<EmitParameter>> mEmitCB; //<! グローバルデータ用コンスタントバッファ
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<Utility::Timer> mTimer;
GlobalData mGlobal;
EmitParameter mEmitParameter;
std::unique_ptr<ImGUI::Window> mWindow;
float mAngle;
float mRadius;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}
}

SpotInstancerParticle::SpotInstancerParticle() {    //カメラの初期化
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,30,-30),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());

    //アルファブレンドの作成
    mAlphaBlend = createAlphaBlend();

    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance().range(0.0f, 1.0f);
    }

    //テクスチャ読み込み
    Utility::getResourceManager()->getTexture()->importResource(Define::TextureType::Smoke, Define::TextureName::SMOKE);

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    mEmitCB = std::make_unique<Graphics::ConstantBuffer<EmitParameter>>(Graphics::ShaderInputType::Compute, 1);
    auto gs = std::make_shared<Graphics::GeometoryShader>("Particle/SpotInstancer_GS");
    auto ps = std::make_shared<Graphics::PixelShader>("Particle/CubeParticle_PS");

    const std::vector<D3D11_INPUT_ELEMENT_DESC>	layouts =
    {
        { "IN_LIFETIME",0, DXGI_FORMAT_R32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "IN_SPEED",0, DXGI_FORMAT_R32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "IN_VELOCITY",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    auto vs = std::make_shared<Graphics::VertexShader>("Particle/SpotInstancer_VS", layouts);

    for (int i = 0; i < NUM; i++) {
        //コンピュートシェーダ作成
        Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
        auto cs = std::make_shared<Graphics::ComputeShader>("Particle/SpotInstancer_CS", info);

        //パーティクルのデータ作成
        std::vector<Particle> particle(COUNT);
        for (int i = 0; i < COUNT; i++) {
            particle[i] = Particle{ -1.0f,0.0f,Math::Vector3::ZERO ,Math::Vector3::ZERO, Graphics::Color4(1.0f,1.0f,1.0f,0.0f) };
        }
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        cs->addSRV(0, randomTable);
        std::vector<int> randomSeed{ Utility::Random::getInstance().range(0,RANDOM_MAX) };

        cs->addUAV(0, randomSeed);

        mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(COUNT,
            Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke),
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

    mTimer = std::make_unique<Utility::Timer>(10.0f);
    mTimer->init();

    mEmitParameter = EmitParameter{ 0 };
    mEmitParameter.center = Math::Vector3::ZERO;
    mAngle = 0.0f;
    mRadius = 10.0f;

    mWindow = std::make_unique<ImGUI::Window>("Parameter");
#define ADD_CHANGE_CENTER_FIELD(name,type) {\
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name,0.0f,[&](float val){\
        type = val; \
    }); \
        mWindow->addItem(field); \
        field->setMinValue(-30.0f); \
        field->setMaxValue(30.0f); \
    }

    ADD_CHANGE_CENTER_FIELD(X, mEmitParameter.center.x);
    ADD_CHANGE_CENTER_FIELD(Y, mEmitParameter.center.y);
    ADD_CHANGE_CENTER_FIELD(Z, mEmitParameter.center.z);
    ADD_CHANGE_CENTER_FIELD(R, mRadius);
}

SpotInstancerParticle::~SpotInstancerParticle() {}

void SpotInstancerParticle::load(Framework::Scene::Collecter& collecter) {}

void SpotInstancerParticle::update() {
    mTimer->update(Utility::Time::getInstance().getDeltaTime());

    mGlobal.deltaTime = Utility::Time::getInstance().getDeltaTime();

    auto calc = [&]() {
        float x = Math::MathUtility::cos(mAngle) * mRadius;
        float z = Math::MathUtility::sin(mAngle) * mRadius;
        return Math::Vector3(x, 10, z) + mEmitParameter.center;
    };

    //グローバルデータのセット
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();
    mEmitParameter.emitTargetIndex = (mEmitParameter.emitTargetIndex + 1) % (THREAD_X * THREAD_Y);

    for (size_t i = 0; i < mGPUParticle.size(); i++) {
        mAngle += 360.0f  * Utility::Time::getInstance().getDeltaTime();
        mEmitParameter.spot = calc();
        mEmitCB->setBuffer(mEmitParameter);
        mEmitCB->sendBuffer();
        mGPUParticle[i]->simulate();
    }
}

bool SpotInstancerParticle::isEndScene() const {
    return false;
}

void SpotInstancerParticle::draw(Framework::Graphics::IRenderer* renderer) {
    Utility::getContext()->RSSetState(ras.Get());
    dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->render();

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Matrix4x4 m = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World, m);
    Utility::getConstantBufferManager()->send();

    for (size_t i = 0; i < mGPUParticle.size(); i++) {
        mGPUParticle[i]->draw();
    }

    mWindow->draw();
}

void SpotInstancerParticle::end() {}

Define::SceneType SpotInstancerParticle::next() {
    return Define::SceneType();
}
