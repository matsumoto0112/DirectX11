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
#include "Framework/Graphics/Renderer/ZTexCreater.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Graphics/Texture/Sampler.h"

using namespace Framework;

namespace {
using ModelList = std::unordered_map<Define::PixelShaderType, std::vector< std::shared_ptr<Graphics::Model>>>;
ModelList mGameModels;
std::unique_ptr<Graphics::OrthographicCamera> mOrthographicCamera;
std::unique_ptr<Graphics::Sprite2D> mSprite;
std::unique_ptr<Graphics::RenderTarget> mRTV;
std::shared_ptr<Framework::Graphics::DirectionalLight> mDirectionalLight;
std::shared_ptr<Framework::Graphics::PointLight> mPointLight;
Math::Vector3 lightPos;
Math::Vector3 lightLookat;
Math::Matrix4x4 lightView;
Math::Matrix4x4 lightProj;
std::unique_ptr<Graphics::ZTexCreater> mZTexCreater;
std::unique_ptr<Graphics::Sampler> mSampler;

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

struct LIGHT {
    Math::Matrix4x4 lightView;
    Math::Matrix4x4 lightProj;
    Math::Vector3 lightPosition;
    float dummy;
};
std::unique_ptr<Graphics::ConstantBuffer<LIGHT>> mConstantBuffer;
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
    vs->importResource(Define::VertexShaderType::Model_Shadow, Define::VertexShaderName::MODEL_SHADOW);
    vs->importResource(Define::VertexShaderType::Model_Shadow_Diffuse, Define::VertexShaderName::MODEL_SHADOW_DIFFUSE);

    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    ps->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);
    ps->importResource(Define::PixelShaderType::Texture2D_Inversion, Define::PixelShaderName::TEXTURE2D_INVERSION);
    ps->importResource(Define::PixelShaderType::Output_Z, Define::PixelShaderName::OUTPUT_Z);
    ps->importResource(Define::PixelShaderType::Model_Shadow, Define::PixelShaderName::MODEL_SHADOW);
    ps->importResource(Define::PixelShaderType::Model_Shadow_Diffuse, Define::PixelShaderName::MODEL_SHADOW_DIFFUSE);
    ps->importResource(Define::PixelShaderType::Model_Shadow_Color, Define::PixelShaderName::MODEL_SHADOW_COLOR);

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
    const int WIDTH = 4096;
    const int HEIGHT = 4096;
    std::shared_ptr<Graphics::TextureBuffer> texBuffer =
        std::make_shared<Graphics::TextureBuffer>(
            Graphics::RenderTargetViewDesc::getDefaultTexture2DDesc(WIDTH, HEIGHT));
    mRTV = std::make_unique<Graphics::RenderTarget>(texBuffer, Graphics::RenderTargetViewDesc::getDefaultRenderTargetViewDesc(),
        std::make_unique<Graphics::Viewport>(Math::Rect(0, 0, WIDTH, HEIGHT)),
        Graphics::SRVFlag::Use);
    mRTV->createDepthStencilView();
    mSprite = std::make_unique<Graphics::Sprite2D>(mRTV->getRenderTargetTexture());

    std::shared_ptr<Graphics::Effect> outputZShader = std::make_shared<Graphics::Effect>(
        vs->getResource(Define::VertexShaderType::Output_Z),
        ps->getResource(Define::PixelShaderType::Output_Z));
    mZTexCreater = std::make_unique<Graphics::ZTexCreater>(4096, 4096, outputZShader);

    const float lightScale = 1.5f;
    lightPos = Math::Vector3(lightScale * -30, lightScale * 30, lightScale * 00);
    lightLookat = Math::Vector3(0, -0, 0);

    mSampler = std::make_unique<Graphics::Sampler>(Graphics::TextureAddressMode::Clamp, Graphics::TextureFilterMode::MinMagMipLinear);

    std::shared_ptr<ImGUI::Window> mUIWindow = std::make_shared<ImGUI::Window>("Light");

#define ADD_LIGHT_POSITION_CHANGE_SLIDER(name,type) {\
    float def = lightPos.##type; \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name, def, [&](float val) { \
        lightPos.##type = val; \
        }); \
    field->setMinValue(-500.0f); \
    field->setMaxValue(500.0f); \
    mUIWindow->addItem(field); \
    }

#define ADD_LIGHT_LOOKAT_CHANGE_SLIDER(name,type) {\
    float def = lightLookat.##type; \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name, def, [&](float val) { \
        lightLookat.##type = val; \
        }); \
    field->setMinValue(-500.0f); \
    field->setMaxValue(500.0f); \
    mUIWindow->addItem(field); \
    }

    ADD_LIGHT_POSITION_CHANGE_SLIDER(PX, x);
    ADD_LIGHT_POSITION_CHANGE_SLIDER(PY, y);
    ADD_LIGHT_POSITION_CHANGE_SLIDER(PZ, z);
    ADD_LIGHT_LOOKAT_CHANGE_SLIDER(LX, x);
    ADD_LIGHT_LOOKAT_CHANGE_SLIDER(LY, y);
    ADD_LIGHT_LOOKAT_CHANGE_SLIDER(LZ, z);
    addDebugUI(mUIWindow);

    mConstantBuffer = std::make_unique<Graphics::ConstantBuffer<LIGHT>>(Graphics::ShaderInputType::Vertex, 10);
}

Main::~Main() {}

void Main::load(Scene::Collecter& collecter) {}

bool flag = false;

void Main::update() {
    mManager->update();
    if (!flag) {
        int num = 0;
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
        parameter.color = Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f);
        parameter.moveSpeed = 3.0f;
        mManager->addEnemy(std::make_unique<NormalEnemy>(tr, parameter, *this));
        flag = true;
    }
}

bool Main::isEndScene() const {
    return false;
}

void Main::draw(Graphics::IRenderer* renderer) {
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    mAlphaBlend->set();
    //Z値を出力する
    mZTexCreater->begin();

    LIGHT l;
    l.lightPosition = Math::Vector3(-10, 10, 0.0f);
    l.lightView = Math::Matrix4x4::createView({ l.lightPosition,Math::Vector3::ZERO,Math::Vector3::UP });
    l.lightProj = Math::Matrix4x4::createProjection({ 45.0f,Math::Vector2(1.0f,1.0f),0.1f,300.0f });

    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::View, l.lightView);
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::Projection, l.lightProj);

    //Z値を出力する描画
    mManager->draw(mZTexCreater.get());
    mZTexCreater->end();

    //本レンダリング開始
    renderer->begin();
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();

    //Clampサンプラーセット
    mSampler->setData(Graphics::ShaderInputType::Pixel, 1);

    //影の描画をする
    setVertexShader(mGameModels, Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Model_Shadow));
    setPixelShader(mGameModels, Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Shadow));

    //Z値を出力したテクスチャをセットする
    mZTexCreater->getRenderedTexture()->setData(Graphics::ShaderInputType::Pixel, 1);
    mCamera->render();

    l.lightProj.transpose();
    l.lightView.transpose();
    mConstantBuffer->setBuffer(l);
    mConstantBuffer->sendBuffer();

    mManager->draw(renderer);
    renderer->end();

    //UIウィンドウ
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
