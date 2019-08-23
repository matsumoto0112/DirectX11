#include "NormalLightingTest.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Graphics/String/TextureString.h"
#include "Framework/Utility/Resource/ResourceManager.h"

using namespace Framework;

NormalLightingTest::NormalLightingTest()
    :mStr(std::make_unique<Graphics::TextureString>("Lighting Test", 14, "")),
    mPerspectiveCamera(std::make_unique<Graphics::PerspectiveCamera>(
        Graphics::PerspectiveCamera::Info{
        Math::Vector3(0.0f,1.0f,-10.0f),
        Math::Vector3(0.0f,1.0f,0.0f),
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,1000.0f
        })),
    mOrthographicCamera(std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize())) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Wall, Define::ModelName::WALL);
    mWall = fbx->getResource(Define::ModelType::Wall);
    Utility::ResourceManager::getInstance().getPixelShader()->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);
    mWall->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Diffuse));
    Math::Quaternion rot;
    rot.setToRotateAboutX(Math::MathUtility::toRadian(-90.0f));
    mWallTransforms.emplace_back(Math::Vector3(0, 0, 0.0f), rot, Math::Vector3(10.0f, 1.0f, 1.0f));
}

NormalLightingTest::~NormalLightingTest() {}

void NormalLightingTest::load(Scene::Collecter& collecter) {}

void NormalLightingTest::update(float delta) {}

bool NormalLightingTest::isEndScene() const {
    return false;
}

void NormalLightingTest::draw() {
    mPerspectiveCamera->setMatrix();
    for (auto&& transform : mWallTransforms) {
        mWall->draw(transform);
    }

    mOrthographicCamera->setMatrix();
    mStr->draw();
}

void NormalLightingTest::end() {}

Define::SceneType NormalLightingTest::next() {
    return Define::SceneType();
}
