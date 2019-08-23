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
        Math::Vector3(0.0f,10.0f,-10.0f),
        Math::Vector3(0.0f,0.0f,0.0f),
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,1000.0f
        })),
    mOrthographicCamera(std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize())) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Wall, Define::ModelName::WALL);
    fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    fbx->importResource(Define::ModelType::Floor, Define::ModelName::FLOOR_NAME);

    mWall = fbx->getResource(Define::ModelType::Wall);
    Utility::ResourceManager::getInstance().getPixelShader()->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);
    mWall->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Diffuse));
    mWallTransforms.emplace_back(
        Math::Vector3(0, 10.0f, 10.0f),
        Math::Quaternion::createRotateAboutX(-90.0f),
        Math::Vector3(10.0f, 1.0f, 10.0f));
    mWallTransforms.emplace_back(
        Math::Vector3(10.0f, 10.0f, 0.0f),
        Math::Quaternion::createRotateAboutX(-90.0f) * Math::Quaternion::createRotateAboutY(90.0f),
        Math::Vector3(10.0f, 1.0f, 10.0f));
    mWallTransforms.emplace_back(
        Math::Vector3(-10.0f, 10.0f, 0.0f),
        Math::Quaternion::createRotateAboutX(-90.0f) * Math::Quaternion::createRotateAboutY(-90.0f),
        Math::Vector3(10.0f, 1.0f, 10.0f));

    mObject.mTransform = Utility::Transform(
        Math::Vector3(0.0f, 0.5f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(0.5f, 0.5f, 0.5f));
    mObject.mModel = fbx->getResource(Define::ModelType::Object);

    mFloor.mTransform = Utility::Transform(
        Math::Vector3(0.0f, -0.0f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(10.0f, 1.0f, 10.0f));
    mFloor.mModel = fbx->getResource(Define::ModelType::Floor);
    mFloor.mModel->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Diffuse));
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
    mObject.draw();
    mFloor.draw();

    mOrthographicCamera->setMatrix();
    mStr->draw();
}

void NormalLightingTest::end() {}

Define::SceneType NormalLightingTest::next() {
    return Define::SceneType();
}

void GameObject::draw() {
    mModel->draw(mTransform);
}
