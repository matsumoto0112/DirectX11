#include "ParticleTest.h"
#include "Framework/Graphics/Particle/SimpleParticleEmitter.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Particle/SimpleParticleEmitter.h"

using namespace Framework;

ParticleTest::ParticleTest() {
    //std::shared_ptr<Graphics::Particle> origin = std::make_shared<Graphics::Particle>();
    //mEmitter = std::make_unique<Graphics::SimpleParticleEmitter>();
}

ParticleTest::~ParticleTest() {}

void ParticleTest::load(Scene::Collecter& collecter) {}

void ParticleTest::update() {}

bool ParticleTest::isEndScene() const {
    return false;
}

void ParticleTest::draw(Graphics::IRenderer* renderer) {}

void ParticleTest::end() {}

Define::SceneType ParticleTest::next() {
    return Define::SceneType();
}
