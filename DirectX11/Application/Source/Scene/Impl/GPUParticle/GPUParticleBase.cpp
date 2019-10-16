#include "GPUParticleBase.h"
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

GPUParticleBase::GPUParticleBase(const GPUParticleInfo& info, const Math::ViewInfo& viewInfo)
    :mInfo(info) {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        viewInfo,
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,100.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());

    mGlobalDataCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    mGlobal.emit = 0;

    mWindow = std::make_unique<ImGUI::Window>("Parameter");
}

GPUParticleBase::~GPUParticleBase() { }

void GPUParticleBase::load(Framework::Scene::Collecter& collecter) {
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

void GPUParticleBase::update() {
    mGlobal.time = Utility::Time::getInstance()->getTime();
    mGlobal.deltaTime = Utility::Time::getInstance()->getDeltaTime();

    //グローバルデータのセット
    mGlobalDataCB->setBuffer(mGlobal);
    mGlobalDataCB->sendBuffer();
}

bool GPUParticleBase::isEndScene() const {
    return false;
}

void GPUParticleBase::draw(Framework::Graphics::IRenderer* pipeline) {
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);
    Utility::getConstantBufferManager()->send();
}

void GPUParticleBase::unload() {
    Graphics::IRenderer* backBufferRenderer = Utility::getRenderingManager()->getRenderer();

    backBufferRenderer->getPipeline()->setRasterizerState(mPrevRasterizer);
    backBufferRenderer->getPipeline()->setAlphaBlend(mPrevAlphaBlend);
    backBufferRenderer->getRenderTarget()->setEnableDepthStencil(true);
}

Define::SceneType GPUParticleBase::next() {
    return Define::SceneType();
}

std::vector<float> GPUParticleBase::createRandomTable() const {
    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance()->range(0.0f, 1.0f);
    }
    return randomTable;
}
