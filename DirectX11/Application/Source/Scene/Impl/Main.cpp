#include "stdafx.h"
#include "Source/Scene/Impl/Main.h"
#include "Source/GameObject/GameObjectManager.h"
#include "Source/GameObject/Player.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Define/Window.h"
#include "Source/GameObject/Bullet/Bullet.h"
#include "Source/GameObject/Enemy/NormalEnemy.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Source/GameObject/Field.h"
#include "Framework/Utility/Random.h"
#include "Source/GameObject/FollowCamera.h"
#include "Source/GameObject/Item/Item.h"

using namespace Framework;

Main::Main() {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Player, Define::ModelName::PLAYER);
    fbx->importResource(Define::ModelType::Plane, Define::ModelName::PLANE);
    fbx->importResource(Define::ModelType::Wall, Define::ModelName::WALL);
    fbx->importResource(Define::ModelType::Bullet, Define::ModelName::BULLET);
    fbx->importResource(Define::ModelType::Enemy, Define::ModelName::ENEMY);
    fbx->importResource(Define::ModelType::Item, Define::ModelName::ITEM);

    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    ps->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);

    fbx->getResource(Define::ModelType::Plane)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));
    fbx->getResource(Define::ModelType::Wall)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));
    fbx->getResource(Define::ModelType::Player)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));
    fbx->getResource(Define::ModelType::Bullet)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_NoTexture));
    fbx->getResource(Define::ModelType::Enemy)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_NoTexture));
    fbx->getResource(Define::ModelType::Item)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));

    std::unique_ptr<Player> player = std::make_unique<Player>(Utility::Transform(), *this);
    std::unique_ptr<Field> field = std::make_unique<Field>(*this);
    mManager = std::make_unique<GameObjectManager>(*this, std::move(player), std::move(field));

    mCamera = std::make_unique<FollowCamera>(Graphics::PerspectiveCamera::Info{
        Math::Vector3(0,10,-10),
        Math::Vector3::ZERO,
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,
        1000.0f },
        getPlayer()->getTransformPtr());

    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.AlphaToCoverageEnable = TRUE;
    bd.IndependentBlendEnable = FALSE;
    bd.RenderTarget[0] = Graphics::AlphaBlendSetting::getAlignmentBlendDesc();
    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(bd);
}

Main::~Main() {}

void Main::load(Scene::Collecter& collecter) {}
static int cnt = 0;
static int num = 0;

void Main::update() {
    mManager->update();
    cnt++;
    if (cnt == 30) {
        cnt = 0;
        const int NUM = 36;
        const float ANGLE = 360.0f / NUM;
        float x = Math::MathUtility::cos(ANGLE * num) * 5;
        float z = Math::MathUtility::sin(ANGLE * num) * 5;
        float s = 0.25f;
        Utility::Transform tr(
            Math::Vector3(x, 0.5f, z),
            Math::Quaternion::IDENTITY,
            Math::Vector3(s, s, s)
        );
        //tr.lookat(Math::Vector3(0.0f, 0.0f, 0.0f));
        mManager->addItem(std::make_unique<Item>(tr, *this));
        num++;
    }
}

bool Main::isEndScene() const {
    return false;
}

void Main::draw() {
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    mAlphaBlend->set();
    mCamera->render();
    mManager->draw();

    for (auto&& window : mDebugUIs) {
        window->draw();
    }
}

void Main::end() {}

Define::SceneType Main::next() {
    return Define::SceneType();
}

FollowCamera* Main::getMainCamera() {
    return mCamera.get();
}

void Main::shotBullet(const Utility::Transform& transform) {
    mManager->addBullet(std::make_unique<Bullet>(transform, *this));
}

void Main::addDebugUI(std::shared_ptr<ImGUI::Window> window) {
    mDebugUIs.emplace_back(window);
}

Player* Main::getPlayer() {
    return mManager->getPlayer();
}
