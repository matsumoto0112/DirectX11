#include "BlackholeParticle.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Graphics/Particle/GPUParticle.h"
#include "Framework/Define/Config.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/Desc/RasterizerStateDesc.h"

using namespace Framework;

namespace {
static constexpr int THREAD_X = 16, THREAD_Y = 4;
static constexpr int DISPATCH_X = 1, DISPATCH_Y = 8;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;

struct Blackhole {
    Math::Vector3 position;
    float radius;
    float theta;
    Graphics::Color4 color;
};

struct GlobalData {
    int emit;
    float time;
    float deltaTime;
    float dummy[1];
};

std::unique_ptr<Graphics::GPUParticle> mGPUParticle; //!< パーティクル
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! グローバルデータ用コンスタントバッファ
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<Utility::Timer> mTimer;
GlobalData mGlobal;
std::shared_ptr<Graphics::RasterizerState> rasterizer;
std::shared_ptr<Graphics::AlphaBlend> alpha;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    return std::make_unique<Graphics::AlphaBlend>(Graphics::BlendStateDesc::BLEND_DESC(Graphics::AlphaBlendType::Add));
}
}

BlackholeParticle::BlackholeParticle() {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());

    //コンピュートシェーダ作成
    Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
    const std::string shaderPath = Define::Path::getInstance()->shader();
    auto gs = std::make_shared<Graphics::GeometoryShader>(shaderPath + "Particle/Geometry/Quad_GS");
    auto ps = std::make_shared<Graphics::PixelShader>(shaderPath + "2D/Texture2D_Color_PS");
    auto cs = std::make_shared<Graphics::ComputeShader>(shaderPath + "Particle/Blackhole/Blackhole_CS", info);
    auto vs = std::make_shared<Graphics::VertexShader>(shaderPath + "Particle/Blackhole/Blackhole_VS");
    {
        //パーティクルのデータ作成
        std::vector<Blackhole> particle(COUNT);
        for (int i = 0; i < COUNT; i++) {
            particle[i] = Blackhole{ Math::Vector3::ZERO,0.0f,0.0f,Graphics::Color4::WHITE };
        }
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        std::vector<float> randomTable(RANDOM_MAX);
        for (int i = 0; i < RANDOM_MAX; i++) {
            randomTable[i] = Utility::Random::getInstance()->range(0.0f, 1.0f);
        }
        cs->addSRV(0, randomTable);

        std::vector<int> randomSeed{ 0 };
        cs->addUAV(0, randomSeed);
    }


    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);

    mGPUParticle = std::make_unique<Graphics::GPUParticle>(COUNT,
        Graphics::TextureLoader().load(Define::Path::getInstance()->texture() + "Smoke.png"),
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
    rasterizer = std::make_shared<Graphics::RasterizerState>(
        Graphics::RasterizerStateDesc::getDefaultDesc(Graphics::FillMode::Solid, Graphics::CullMode::None));
    alpha = std::make_shared<Graphics::AlphaBlend>(
        Graphics::BlendStateDesc::BLEND_DESC(Graphics::AlphaBlendType::Add));
    mTimer = std::make_unique<Utility::Timer>(10.0f);
    mTimer->init();

    mGlobal.emit = 1;
}

BlackholeParticle::~BlackholeParticle() { }

void BlackholeParticle::load(Framework::Scene::Collecter& collecter) {
    Utility::getRenderingManager()->getRenderer()->getPipeline()->setRasterizerState(rasterizer);
    Utility::getRenderingManager()->getRenderer()->getPipeline()->setAlphaBlend(alpha);
    Utility::getRenderingManager()->getRenderer()->getRenderTarget()->setEnableDepthStencil(false);
    int a = 0;
}

void BlackholeParticle::update() {
    mTimer->update(Utility::Time::getInstance()->getDeltaTime());

    mGlobal.time = Utility::Time::getInstance()->getTime();
    mGlobal.deltaTime = Utility::Time::getInstance()->getDeltaTime();

    //グローバルデータのセット
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();

    mGlobal.emit = 0;

    mGPUParticle->simulate();
}

bool BlackholeParticle::isEndScene() const {
    return false;
}

void BlackholeParticle::draw(Framework::Graphics::IRenderer* pipeline) {
    Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 0.3f));
    Math::Matrix4x4 m = Math::Matrix4x4::createScale(Math::Vector3(0.1f, 0.1f, 1.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    Utility::getConstantBufferManager()->send();

    mGPUParticle->draw();
}

void BlackholeParticle::end() { }

Define::SceneType BlackholeParticle::next() {
    return Define::SceneType();
}
