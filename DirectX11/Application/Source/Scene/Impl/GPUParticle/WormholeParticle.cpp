#include "WormholeParticle.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Utility/Time.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Graphics/Particle/GPUParticle.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Source/Utility/Shader/ShaderLoad.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/Desc/RasterizerStateDesc.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"

using namespace Framework;

namespace {
constexpr int NUM = 256;

struct ParticleParameter {
    UINT index;
    Math::Vector3 spot;
    Math::Vector3 center;
    float radius;
};

std::vector<std::unique_ptr<Graphics::GPUParticle>> mGPUParticle; //!< パーティクル
std::unique_ptr<Graphics::ConstantBuffer<ParticleParameter>> mParameterCB; //<! パラメータ用コンスタントバッファ
ParticleParameter mParameter;
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mText;
int mNum;
float mSpeed;
float mMaxYPosition;

}

WormholeParticle::WormholeParticle() {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0, 30, -30),Math::Vector3(0, 0, 0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());

    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance()->range(0.0f, 1.0f);
    }

    mParameterCB = std::make_unique<Graphics::ConstantBuffer<ParticleParameter>>(Graphics::ShaderInputType::Compute, 1);
    auto gs = ShaderLoad::loadGS("Particle/Geometry/Cube_GS");
    auto ps = ShaderLoad::loadPS("Particle/Output_Color_PS");
    auto vs = ShaderLoad::loadVS("Particle/Wormhole/VS");

    for (int i = 0; i < NUM; i++) {
        //コンピュートシェーダ作成
        Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
        auto cs = ShaderLoad::loadCS("Particle/Wormhole/CS", info);

        //パーティクルのデータ作成
        std::vector<Particle> particle(COUNT);
        for (int i = 0; i < COUNT; i++) {
            particle[i] = Particle{ -1.0f,0.0f ,Math::Vector3::ZERO,Math::Vector3::ZERO, Graphics::Color4(1.0f,1.0f,1.0f,0.0f) };
        }
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        cs->addSRV(0, randomTable);
        std::vector<int> randomSeed{ Utility::Random::getInstance()->range(0,RANDOM_MAX) };

        cs->addUAV(0, randomSeed);

        mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(COUNT,
            Graphics::TextureLoader().load(Define::Path::getInstance()->texture() + "Circle.png"),
            cs,
            vs,
            ps,
            gs));
    }   
    mGlobalDataCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);

    mSpeed = 30.0f;
    mParameter.index = -1;
    mParameter.spot = Math::Vector3::ZERO;
    mParameter.radius = 10.0f;
    mNum = 10;
    mMaxYPosition = 20.0f;

    mWindow = std::make_unique<ImGUI::Window>("Parameter");
    mText = std::make_shared<ImGUI::Text>("");
    mWindow->addItem(mText);

    mTimer = std::make_unique<Utility::Timer>(10.0f);
    mTimer->init();


#define ADD_CHANGE_FIELD(name,var,min,max) { \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name,var,[&](float val){var = val;}); \
    mWindow->addItem(field); \
    field->setMinValue(min); \
    field->setMaxValue(max); \
    }

    ADD_CHANGE_FIELD(RADIUS, mParameter.radius, 0.0f, 30.0f);
    ADD_CHANGE_FIELD(SPEED, mSpeed, 0.0f, 100.0f);
    ADD_CHANGE_FIELD(MAX_Y, mMaxYPosition, 0.0f, 100.0f);
    ADD_CHANGE_FIELD(NUM, mNum, 0, NUM);
}

WormholeParticle::~WormholeParticle() { }

void WormholeParticle::load(Scene::Collecter& collecter) {
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

void WormholeParticle::update() {
    mTimer->update(Utility::Time::getInstance()->getDeltaTime());

    mGlobal.time = Utility::Time::getInstance()->getTime();
    mGlobal.deltaTime = Utility::Time::getInstance()->getDeltaTime();

    //グローバルデータのセット
    mGlobal.emit = 0;
    mGlobalDataCB->setBuffer(mGlobal);
    mGlobalDataCB->sendBuffer();

    mParameter.index = (mParameter.index + 1) % (THREAD_X * THREAD_Y);

    mParameter.spot.y += 1.0f * mSpeed *  Utility::Time::getInstance()->getDeltaTime();
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

void WormholeParticle::draw(Framework::Graphics::IRenderer* pipeline) {

    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Matrix4x4 m = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    Utility::getConstantBufferManager()->send();

    for (int i = 0; i < mNum; i++) {
        mGPUParticle[i]->draw();
    }

    mText->setText(Utility::StringBuilder("") << mNum * COUNT);
    mWindow->draw();
}

void WormholeParticle::unload() {
    Graphics::IRenderer* backBufferRenderer = Utility::getRenderingManager()->getRenderer();

    backBufferRenderer->getPipeline()->setRasterizerState(mPrevRasterizer);
    backBufferRenderer->getPipeline()->setAlphaBlend(mPrevAlphaBlend);
    backBufferRenderer->getRenderTarget()->setEnableDepthStencil(true);
}

Define::SceneType WormholeParticle::next() {
    return Define::SceneType();
}
