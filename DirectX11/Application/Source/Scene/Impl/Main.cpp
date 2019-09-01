#include "Source/Scene/Impl/Main.h"
#include "Source/GameObject/GameObjectManager.h"
#include "Source/GameObject/Player.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Define/Window.h"
#include "Source/GameObject/Wall.h"
using namespace Framework;

Main::Main() {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Player, Define::ModelName::PLAYER);
    fbx->importResource(Define::ModelType::Plane, Define::ModelName::PLANE);
    fbx->importResource(Define::ModelType::Red, Define::ModelName::RED);
    fbx->importResource(Define::ModelType::Blue, Define::ModelName::BLUE);
    fbx->importResource(Define::ModelType::Green, Define::ModelName::GREEN);
    fbx->importResource(Define::ModelType::Wall, Define::ModelName::WALL);

    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    ps->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);

    std::unique_ptr<GameObject> player = std::make_unique<Player>(Utility::Transform());
    mManager = std::make_unique<GameObjectManager>(std::move(player));
    mManager->addWall(std::make_unique<Wall>(Utility::Transform(
        Math::Vector3(-10.0f, 2.5f, 0.0f),
        Math::Quaternion::createRotateAboutY(90.0f),
        Math::Vector3(0.01f, 0.01f, 0.01f)
    )));

    mCamera = std::make_unique<Graphics::PerspectiveCamera>(Graphics::PerspectiveCamera::Info{
        Math::Vector3(0,10,-10),
        Math::Vector3::ZERO,
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,
        1000.0f
        });
}

Main::~Main() {}

void Main::load(Scene::Collecter& collecter) {}

void Main::update() {
    mManager->update();
}

bool Main::isEndScene() const {
    return false;
}

void Main::draw() {
    mCamera->render();
    mManager->draw();

}

void Main::end() {}

Define::SceneType Main::next() {
    return Define::SceneType();
}
