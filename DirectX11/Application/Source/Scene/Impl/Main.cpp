#include "stdafx.h"
#include "Source/Scene/Impl/Main.h"
#include "Source/GameObject/GameObjectManager.h"
#include "Source/GameObject/Player.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Define/Window.h"
#include "Source/GameObject/Bullet/Bullet.h"
#include "Source/GameObject/Enemy/Enemy.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Source/GameObject/Field.h"
#include "Framework/Utility/Random.h"

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
    window->addItem(field); \
}

using namespace Framework;
namespace {
std::shared_ptr<ImGUI::Text> mHitText;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizerState;
std::unique_ptr<Graphics::AlphaBlend> mAlphaBlend;
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

    std::unique_ptr<Player> player = std::make_unique<Player>(Utility::Transform(), *this);
    std::unique_ptr<Field> field = std::make_unique<Field>(*this);
    mManager = std::make_unique<GameObjectManager>(*this, std::move(player), std::move(field));

    mCamera = std::make_unique<Graphics::PerspectiveCamera>(Graphics::PerspectiveCamera::Info{
        Math::Vector3(0,10,-10),
        Math::Vector3::ZERO,
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,
        1000.0f
        });

    std::unique_ptr<ImGUI::Window> window = std::make_unique<ImGUI::Window>("Camera");


    ADD_CAMERA_POSITION_CHANGE_FIELD(X, x);
    ADD_CAMERA_POSITION_CHANGE_FIELD(Y, y);
    ADD_CAMERA_POSITION_CHANGE_FIELD(Z, z);
    std::shared_ptr<ImGUI::Button> button = std::make_shared<ImGUI::Button>("RESET", [&]() {mCamera->setLookat(Math::Vector3::ZERO); });
    window->addItem(button);
    addDebugUI(std::move(window));

    // ラスタライザの設定
    D3D11_RASTERIZER_DESC rdc = {};
    rdc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
    rdc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rdc.FrontCounterClockwise = TRUE;
    Utility::getDevice()->CreateRasterizerState(&rdc, &pRasterizerState);

    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.AlphaToCoverageEnable = FALSE;
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
    if (cnt == 60) {
        cnt = 0;
        const int NUM = 36;
        const float ANGLE = 360.0f / NUM;
        float x = Math::MathUtility::cos(ANGLE * num) * 5;
        float z = Math::MathUtility::sin(ANGLE * num) * 5;
        float s = Utility::Random::getInstance().range(1.0f, 2.0f);
        Utility::Transform tr(
            Math::Vector3(x, 0, z),
            Math::Quaternion::IDENTITY,
            Math::Vector3(s, s, s)
        );
        tr.lookat(Math::Vector3(0.0f, 0.0f, 0.0f));
        mManager->addEnemy(std::make_unique<Enemy>(tr, Graphics::Color4(0.0f, 0.0f, 1.0f, 1.0f), *this));
        num++;
    }
}

bool Main::isEndScene() const {
    return false;
}

void Main::draw() {
    mAlphaBlend->set();
    //Utility::getContext()->RSSetState(pRasterizerState.Get());
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

Graphics::PerspectiveCamera* Main::getMainCamera() {
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
