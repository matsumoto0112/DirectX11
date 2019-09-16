#include "ParticleTest.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Time.h"
#include "Source/Particle/SmokeParticleEmitter.h"

using namespace Framework;
namespace {
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mParticleNum;
}

ParticleTest::ParticleTest() {
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());

    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(desc);
    Utility::getResourceManager()->getTexture()->importResource(Define::TextureType::Smoke, Define::TextureName::SMOKE);

    std::shared_ptr<Graphics::Sprite3D> sprite = std::make_shared<Graphics::Sprite3D>(Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke));
    sprite->setAlpha(0.1f);
    std::shared_ptr<Graphics::Particle> origin = std::make_shared<Graphics::Particle>(sprite);
    origin->setLifeTime(10.0f);
    mEmitter = std::make_unique<SmokeParticleEmitter>(origin);
    mEmitter->getLimitTimer().setLimitTime(100.0f);
    mEmitter->getEmitTimer().setLimitTime(0.1f);
    mEmitter->setOnceEmitNum(10);
    mEmitter->setMaxParticleNum(200);
    mEmitter->getVelocityRange().setMin(Math::Vector3(-0.25f, 1.0f, 0.0f));
    mEmitter->getVelocityRange().setMax(Math::Vector3(0.25f, 1.0f, 0.0f));
    mEmitter->init();

    mWindow = std::make_unique<ImGUI::Window>("Particle Parameter");
    mParticleNum = std::make_shared<ImGUI::Text>("0");
    mWindow->addItem(mParticleNum);
}

ParticleTest::~ParticleTest() {}

void ParticleTest::load(Scene::Collecter& collecter) {}

void ParticleTest::update() {
    mEmitter->simulate(Utility::Time::getInstance().getDeltaTime());

    mParticleNum->setText(Utility::StringBuilder("") << mEmitter->getParticleNum());
}

bool ParticleTest::isEndScene() const {
    return false;
}

void ParticleTest::draw(Graphics::IRenderer* renderer) {
    Graphics::BackBufferRenderer* back = dynamic_cast<Graphics::BackBufferRenderer*>(renderer);
    mAlphaBlend->set();
    back->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->render();
    mEmitter->draw(renderer);

    mWindow->draw();
}

void ParticleTest::end() {}

Define::SceneType ParticleTest::next() {
    return Define::SceneType();
}
