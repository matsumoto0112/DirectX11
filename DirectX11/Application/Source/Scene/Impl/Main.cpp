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
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"
#include "Framework/Graphics/Shader/Effect.h"

using namespace Framework;

namespace {
using ModelList = std::unordered_map<Define::PixelShaderType, std::vector< std::shared_ptr<Graphics::Model>>>;
ModelList mGameModels;
std::unique_ptr<Graphics::OrthographicCamera> mOrthographicCamera;
std::unique_ptr<Graphics::Sprite2D> mSprite;
std::unique_ptr<Graphics::RenderTarget> mRTV;

void setDefaultPixelShader(ModelList& list) {
    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    for (auto&& modelSet : list) {
        for (auto&& model : modelSet.second) {
            model->setPixelShader(ps->getResource(modelSet.first));
        }
    }
}

void setVertexShader(ModelList& list, std::shared_ptr<Graphics::VertexShader> vs) {
    for (auto&& modelSet : list) {
        for (auto&& model : modelSet.second) {
            model->setVertexShader(vs);
        }
    }
}

void setPixelShader(ModelList& list, std::shared_ptr<Graphics::PixelShader> ps) {
    for (auto&& modelSet : list) {
        for (auto&& model : modelSet.second) {
            model->setPixelShader(ps);
        }
    }
}
}

Main::Main() {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Player, Define::ModelName::PLAYER);
    fbx->importResource(Define::ModelType::Plane, Define::ModelName::PLANE);
    fbx->importResource(Define::ModelType::Wall, Define::ModelName::WALL);
    fbx->importResource(Define::ModelType::Bullet, Define::ModelName::BULLET);
    fbx->importResource(Define::ModelType::Enemy, Define::ModelName::ENEMY);
    fbx->importResource(Define::ModelType::Item, Define::ModelName::ITEM);

    auto vs = Utility::ResourceManager::getInstance().getVertexShader();
    vs->importResource(Define::VertexShaderType::Output_Z, Define::VertexShaderName::OUTPUT_Z);

    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    ps->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);
    ps->importResource(Define::PixelShaderType::Texture2D_Inversion, Define::PixelShaderName::TEXTURE2D_INVERSION);
    ps->importResource(Define::PixelShaderType::Output_Z, Define::PixelShaderName::OUTPUT_Z);

    mGameModels[Define::PixelShaderType::Model_Diffuse].emplace_back(fbx->getResource(Define::ModelType::Plane));
    mGameModels[Define::PixelShaderType::Model_Diffuse].emplace_back(fbx->getResource(Define::ModelType::Wall));
    mGameModels[Define::PixelShaderType::Model_Diffuse].emplace_back(fbx->getResource(Define::ModelType::Player));
    mGameModels[Define::PixelShaderType::Model_NoTexture].emplace_back(fbx->getResource(Define::ModelType::Bullet));
    mGameModels[Define::PixelShaderType::Model_NoTexture].emplace_back(fbx->getResource(Define::ModelType::Enemy));
    mGameModels[Define::PixelShaderType::Model_Diffuse].emplace_back(fbx->getResource(Define::ModelType::Item));
    setDefaultPixelShader(mGameModels);

    std::unique_ptr<Player> player = std::make_unique<Player>(Utility::Transform(), *this);
    std::unique_ptr<Field> field = std::make_unique<Field>(*this);
    mManager = std::make_unique<GameObjectManager>(*this, std::move(player), std::move(field));

    Math::ViewInfo v{
        Math::Vector3(0,10,-10),
        Math::Vector3::ZERO,
        Math::Vector3::UP
    };
    Math::ProjectionInfo p{
        45.0f,
        Define::Window::getSize(),
        0.1f,
        1000.0f
    };
    mCamera = std::make_unique<FollowCamera>(v, p,
        getPlayer()->getTransformPtr());

    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.AlphaToCoverageEnable = FALSE;
    bd.IndependentBlendEnable = FALSE;
    bd.RenderTarget[0] = Graphics::AlphaBlendSetting::getAlignmentBlendDesc();
    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(bd);

    mOrthographicCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());
    std::shared_ptr<Graphics::TextureBuffer> texBuffer =
        std::make_shared<Graphics::TextureBuffer>(
            Graphics::RenderTargetViewDesc::getDefaultTexture2DDesc(Define::Window::WIDTH, Define::Window::HEIGHT));
    mRTV = std::make_unique<Graphics::RenderTarget>(texBuffer, Graphics::RenderTargetViewDesc::getDefaultRenderTargetViewDesc(),
        std::make_unique<Graphics::Viewport>(Math::Rect(0, 0, Define::Window::WIDTH, Define::Window::HEIGHT)),
        Graphics::SRVFlag::Use);
    mRTV->createDepthStencilView();
    mSprite = std::make_unique<Graphics::Sprite2D>(mRTV->getRenderTargetTexture());
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
        float s = 1.0f;
        Utility::Transform tr(
            Math::Vector3(x, 0.0f, z),
            Math::Quaternion::IDENTITY,
            Math::Vector3(s, s, s)
        );
        tr.lookat(Math::Vector3(0.0f, 0.0f, 0.0f));
        NormalEnemy::Parameter parameter;
        parameter.color = Graphics::Color4(1.0f, 1.0f, 0.0f, 1.0f);
        parameter.moveSpeed = 3.0f;
        mManager->addEnemy(std::make_unique<NormalEnemy>(tr, parameter, *this));
        num++;
    }
}

bool Main::isEndScene() const {
    return false;
}

void Main::draw() {
    mRTV->set();
    mRTV->clear();

    auto vs = Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Output_Z);
    auto ps = Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Output_Z);
    setVertexShader(mGameModels, vs);
    setPixelShader(mGameModels, ps);

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    mAlphaBlend->set();
    mCamera->render();
    mManager->draw();
    Utility::getRenderingManager()->setBackbuffer(Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));

    mOrthographicCamera->render();
    mSprite->setTexture(mRTV->getRenderTargetTexture(), false);
    mSprite->draw();

    setDefaultPixelShader(mGameModels);
    setVertexShader(mGameModels, Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Model));

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
