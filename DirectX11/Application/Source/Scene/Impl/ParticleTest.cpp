#include "ParticleTest.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Particle/SimpleParticleEmitter.h"
#include "Framework/Graphics/Particle/SimpleParticleEmitter.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Time.h"

using namespace Framework;

ParticleTest::ParticleTest() {
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());

    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = TRUE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(desc);
    Utility::getResourceManager()->getTexture()->importResource(Define::TextureType::Smoke, Define::TextureName::SMOKE);

    std::shared_ptr<Graphics::Sprite3D> sprite = std::make_shared<Graphics::Sprite3D>(Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke));
    std::shared_ptr<Graphics::Particle> origin = std::make_shared<Graphics::Particle>(sprite);
    mEmitter = std::make_unique<Graphics::SimpleParticleEmitter>(origin);
    mEmitter->init();
}

ParticleTest::~ParticleTest() {}

void ParticleTest::load(Scene::Collecter& collecter) {}

void ParticleTest::update() {
    mEmitter->simulate(Utility::Time::getInstance().getDeltaTime());
}

bool ParticleTest::isEndScene() const {
    return false;
}

void ParticleTest::draw(Graphics::IRenderer* renderer) {
    //Graphics::BackBufferRenderer* back = dynamic_cast<Graphics::BackBufferRenderer*>(renderer);
    //back->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->render();
    mEmitter->draw(renderer);
}

void ParticleTest::end() {}

Define::SceneType ParticleTest::next() {
    return Define::SceneType();
}
