#include "stdafx.h"
#include "Source/Scene/Impl/Main.h"
#include "Source/GameObject/GameObjectManager.h"
#include "Source/GameObject/Player.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Define/Window.h"
#include "Source/GameObject/Wall.h"
#include "Source/GameObject/Floor.h"
#include "Source/GameObject/Bullet.h"
#include "Source/GameObject/Enemy/Enemy.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

#include "Framework/Graphics/Renderer/3D/Cube.h"

#define ADD_CAMERA_POSITION_CHANGE_FIELD(name,type) { \
    const float defValue  = mCamera->getPosition().##type; \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name, defValue,[&](float val){ \
        Math::Vector3 pos = mCamera->getPosition(); \
        Math::Vector3 look = mCamera->getLookat(); \
        const float sub = pos.##type -  val; \
        look.##type -= sub ; \
        pos.##type= val ; \
        mCamera->setPosition(pos); \
        mCamera->setLookat(look); \
    }); \
    field ->setMinValue(-50.0f); \
    field->setMaxValue(50.0f); \
    mUIWindow->addItem(field); \
}

using namespace Framework;
namespace {
std::unique_ptr<ImGUI::Window> mUIWindow;
std::unique_ptr<Graphics::Cube> mOBB;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizerState;
}

Main::Main() {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Player, Define::ModelName::PLAYER);
    fbx->importResource(Define::ModelType::Plane, Define::ModelName::PLANE);
    fbx->importResource(Define::ModelType::Red, Define::ModelName::RED);
    fbx->importResource(Define::ModelType::Blue, Define::ModelName::BLUE);
    fbx->importResource(Define::ModelType::Green, Define::ModelName::GREEN);
    fbx->importResource(Define::ModelType::Wall, Define::ModelName::WALL);
    fbx->importResource(Define::ModelType::Bullet, Define::ModelName::BULLET);
    fbx->importResource(Define::ModelType::Enemy, Define::ModelName::ENEMY);

    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    ps->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);

    fbx->getResource(Define::ModelType::Plane)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));
    fbx->getResource(Define::ModelType::Wall)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));
    fbx->getResource(Define::ModelType::Player)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));
    fbx->getResource(Define::ModelType::Bullet)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_NoTexture));
    fbx->getResource(Define::ModelType::Enemy)->setPixelShader(ps->getResource(Define::PixelShaderType::Model_NoTexture));

    std::unique_ptr<GameObject> player = std::make_unique<Player>(Utility::Transform(), *this);
    std::unique_ptr<Floor> floor = std::make_unique<Floor>(Utility::Transform(
        Math::Vector3(0, 0, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(5, 1, 5)
    ));
    mManager = std::make_unique<GameObjectManager>(std::move(player), std::move(floor));
    mManager->addWall(std::make_unique<Wall>(Utility::Transform(
        Math::Vector3(-10.0f, 0.0f, 0.0f),
        Math::Quaternion::createRotateAboutY(90.0f),
        Math::Vector3(1.0f, 1.0f, 1.0f)
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

    mUIWindow = std::make_unique<ImGUI::Window>("Camera");


    ADD_CAMERA_POSITION_CHANGE_FIELD(X, x);
    ADD_CAMERA_POSITION_CHANGE_FIELD(Y, y);
    ADD_CAMERA_POSITION_CHANGE_FIELD(Z, z);

    mManager->addEnemy(std::make_unique<Enemy>(Utility::Transform(
        Math::Vector3(0, 0, 5),
        Math::Quaternion::IDENTITY,
        Math::Vector3(0.05f, 0.05f, 0.05f)
    )));

    mOBB = std::make_unique<Graphics::Cube>();

    // ラスタライザの設定
    D3D11_RASTERIZER_DESC rdc = {};
    rdc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rdc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rdc.FrontCounterClockwise = TRUE;
    Utility::getDevice()->CreateRasterizerState(&rdc, &pRasterizerState);


}

Main::~Main() {}

void Main::load(Scene::Collecter& collecter) {}

void Main::update() {
    mManager->update();
}

bool Main::isEndScene() const {
    return false;
}

float f = 0.0f;
void Main::draw() {
    mCamera->render();
    //mManager->draw();
    Graphics::Color4 color = Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f);
    Utility::getContext()->RSSetState(pRasterizerState.Get());
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
    Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Only_Position)->set();
    Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::OutPot_Color)->set();
    Math::Quaternion rot =
        Math::Quaternion::createRotateAboutY(f * 0.25f)
        * Math::Quaternion::createRotateAboutZ(f * 0.7f)
        * Math::Quaternion::createRotateAboutX(f);
    f += 5.0f;
    Utility::Transform tr(Math::Vector3::ZERO, rot, Math::Vector3(1.0f, 1.0f, 1.0f));
    mOBB->render(tr);
    //mUIWindow->draw();
}

void Main::end() {}

Define::SceneType Main::next() {
    return Define::SceneType();
}

Graphics::PerspectiveCamera* Main::getMainCamera() {
    return mCamera.get();
}

void Main::shotBullet(const Utility::Transform& transform) {
    mManager->addBullet(std::make_unique<Bullet>(transform));
}
