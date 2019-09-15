#include "ParticleTest.h"
#include "Framework/Graphics/Particle/SimpleParticleEmitter.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Particle/SimpleParticleEmitter.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Time.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Renderer/IRenderer.h"

using namespace Framework;

ParticleTest::ParticleTest() {
    mCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

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
    renderer->setCurrentPerspectiveCamera(mCamera.get());
    mCamera->render();
    mEmitter->draw(renderer);
}

void ParticleTest::end() {}

Define::SceneType ParticleTest::next() {
    return Define::SceneType();
}
