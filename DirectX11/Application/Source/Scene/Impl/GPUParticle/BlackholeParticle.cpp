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
#include "Source/Utility/Shader/ShaderLoad.h"

using namespace Framework;

BlackholeParticle::BlackholeParticle() {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());

    //コンピュートシェーダ作成
    Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
    auto cs = ShaderLoad::loadCS("Particle/Blackhole/CS", info);
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
        ShaderLoad::loadVS("Particle/Blackhole/VS"),
        ShaderLoad::loadPS("2D/Texture2D_Color_PS"),
        ShaderLoad::loadGS("Particle/Geometry/Quad_GS"));

    mTimer = std::make_unique<Utility::Timer>(10.0f);
    mTimer->init();

    mGlobal.emit = -1;
}

BlackholeParticle::~BlackholeParticle() { }

void BlackholeParticle::load(Framework::Scene::Collecter& collecter) {
    //このシーンで使用するステートを作成する
    auto newRasterizer = std::make_shared<Graphics::RasterizerState>(
        Graphics::RasterizerStateDesc::getDefaultDesc(Graphics::FillMode::Solid, Graphics::CullMode::None));
    auto newBlendState = std::make_shared<Graphics::AlphaBlend>(
        Graphics::BlendStateDesc::BLEND_DESC(Graphics::AlphaBlendType::Add));

    //前の状態をコピーしておく
    //シーン終了時にもとに戻してあげる
    Graphics::IRenderer* backBufferRenderer = Utility::getRenderingManager()->getRenderer();
    mPrevRasterizer = backBufferRenderer->getPipeline()->getRasterizerState();
    mPrevAlphaBlend = backBufferRenderer->getPipeline()->getAlphaBlend();

    backBufferRenderer->getPipeline()->setRasterizerState(newRasterizer);
    backBufferRenderer->getPipeline()->setAlphaBlend(newBlendState);
    backBufferRenderer->getRenderTarget()->setEnableDepthStencil(false);
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
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 0.3f));
    Math::Matrix4x4 m = Math::Matrix4x4::createScale(Math::Vector3(0.1f, 0.1f, 1.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    Utility::getConstantBufferManager()->send();

    mGPUParticle->draw();
}

void BlackholeParticle::unload() {
    Graphics::IRenderer* backBufferRenderer = Utility::getRenderingManager()->getRenderer();

    backBufferRenderer->getPipeline()->setRasterizerState(mPrevRasterizer);
    backBufferRenderer->getPipeline()->setAlphaBlend(mPrevAlphaBlend);
    backBufferRenderer->getRenderTarget()->setEnableDepthStencil(true);
}

Define::SceneType BlackholeParticle::next() {
    return Define::SceneType();
}
