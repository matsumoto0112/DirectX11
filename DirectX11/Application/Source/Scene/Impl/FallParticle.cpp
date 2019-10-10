#include "FallParticle.h"
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
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Graphics/Particle/GPUParticle.h"

using namespace Framework;

namespace {
static constexpr int THREAD_X = 16, THREAD_Y = 16;
static constexpr int DISPATCH_X = 8, DISPATCH_Y = 8;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;

struct Particle {
    float lifeTime;
    Math::Vector3 position;
    Math::Vector3 velocity;
    Graphics::Color4 color;
};

struct GlobalData {
    float deltaTime;
    float gravity;
    float dummy[2];
};

std::unique_ptr<Graphics::GPUParticle> mGPUParticle; //!< パーティクル
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! グローバルデータ用コンスタントバッファ
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<Utility::Timer> mTimer;
GlobalData mGlobal;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}
}
FallParticle::FallParticle() {    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());

    //アルファブレンドの作成
    mAlphaBlend = createAlphaBlend();


    //コンピュートシェーダ作成
    Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
    auto cs = std::make_shared<Graphics::ComputeShader>("Particle/Fall_CS", info);

    //パーティクルのデータ作成
    std::vector<Particle> particle(COUNT);
    for (int i = 0; i < COUNT; i++) {
        particle[i] = Particle{ -1.0f,Math::Vector3::ZERO,Math::Vector3::ZERO,Graphics::Color4::WHITE };
    }
    cs->addUAVEnableVertexBuffer(1, particle, 0);

    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance()->range(0.0f, 1.0f);
    }
    cs->addSRV(0, randomTable);

    std::vector<int> randomSeed{ 0 };
    cs->addUAV(0, randomSeed);

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    auto gs = std::make_shared<Graphics::GeometoryShader>("SimpleParticleGS");
    auto ps = std::make_shared<Graphics::PixelShader>("2D/Texture2D_Color_PS");
    auto vs = std::make_shared<Graphics::VertexShader>("Particle/Fall_VS");

    mGPUParticle = std::make_unique<Graphics::GPUParticle>(COUNT,
        Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke),
        cs,
        vs,
        ps,
        gs);


    //ラスタライザ作成
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Graphics::DX11InterfaceAccessor::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());

    mTimer = std::make_unique<Utility::Timer>(10.0f);
    mTimer->init();
}

FallParticle::~FallParticle() {}

void FallParticle::load(Framework::Scene::Collecter& collecter) {}

void FallParticle::update() {
    mTimer->update(Utility::Time::getInstance()->getDeltaTime());

    mGlobal.deltaTime = Utility::Time::getInstance()->getDeltaTime();
    mGlobal.gravity = 9.8f;

    //グローバルデータのセット
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();

    mGPUParticle->simulate();
}

bool FallParticle::isEndScene() const {
    return false;
}

void FallParticle::draw(Framework::Graphics::IRenderer* renderer) {
    //Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    //dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    //renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    //mAlphaBlend->set();
    //Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    //Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    //Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    //Math::Matrix4x4 m = Math::Matrix4x4::createScale(Math::Vector3(1.0f, 1.0f, 1.0f));
    //Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    //Utility::getConstantBufferManager()->send();

    //mGPUParticle->draw();
}

void FallParticle::end() {}

Define::SceneType FallParticle::next() {
    return Define::SceneType();
}
