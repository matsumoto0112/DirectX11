#include "ParticleTest.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/String/TextureString.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/Particle/SimpleParticleEmitter.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Random.h"
#include "Framework/Define/Window.h"

namespace {
std::shared_ptr<Framework::Graphics::Model> model;
}

using namespace Framework;

ParticleTest::ParticleTest()
    :mParticleStr(std::make_unique<Graphics::TextureString>("P", 28, "")) {
    std::shared_ptr<Graphics::Sprite3D> sprite = std::make_shared<Graphics::Sprite3D>(Graphics::TextureLoader().load(Define::Path::getInstance().texture() + "red_dot.png"));
    std::shared_ptr<Graphics::Particle> origin = std::make_shared<Graphics::Particle>(sprite);
    origin->setVelocity(Math::Vector3(0.0f, 1.0f, 0.0f));
    origin->setLifeTime(10.0f);
    mParticle = std::make_unique<Graphics::SimpleParticleEmitter>(origin);

    //Utility::ResourceManager::getInstance().getFBXModel()->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    //model = Utility::ResourceManager::getInstance().getFBXModel()->getResource(Define::ModelType::Object);
    model->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model));
}

ParticleTest::~ParticleTest() {}

void ParticleTest::load(Framework::Scene::Collecter& collecter) {}

void ParticleTest::update() {}

bool ParticleTest::isEndScene() const {
    return false;
}

void ParticleTest::draw() {
    Math::Matrix4x4 proj = Math::Matrix4x4::createOrthographic(Define::Window::getSize());
    Math::Matrix4x4 view = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::Projection, proj);
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::View, view);

    mParticleStr->draw();
}

void ParticleTest::end() {}

Define::SceneType ParticleTest::next() {
    return Define::SceneType::Title;
}
