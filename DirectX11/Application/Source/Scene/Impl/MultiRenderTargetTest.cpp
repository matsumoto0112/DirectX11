#include "MultiRenderTargetTest.h"
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Define/Window.h"
#include "Framework/Utility/ImGUI/Window.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Shader/ShaderResourceView.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Graphics/Render/MultiRenderTarget.h"
#include "Framework/Utility/ImGUI/Button.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"

using namespace Framework;

namespace {
struct Tmp {
    static constexpr int RTV_NUM = 4;
    std::unique_ptr<Graphics::AlphaBlend> mAlphaBlend;
    std::unique_ptr<Graphics::Sprite2D> mSprite;
    std::unique_ptr<Graphics::MultiRenderTarget> mRenderTargetViews;
};
std::unique_ptr<Tmp> mTmp;
}

MultiRenderTargetTest::MultiRenderTargetTest()
    :mPerspectiveCamera(std::make_unique<Graphics::PerspectiveCamera>(
        Graphics::PerspectiveCamera::Info{
            Math::Vector3(0,0,-10),
            Math::Vector3(0,0,0),
            Math::Vector3::UP,
            45.0f,
            Define::Window::getSize(),
            0.1f,
            1000.0f
        })),
    mOrthographicCamera(std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize())) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Enemy, Define::ModelName::ENEMY_NAME);
    mEnemy.mModel = fbx->getResource(Define::ModelType::Enemy);
    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    ps->importResource(Define::PixelShaderType::Model_Diffuse_Split4Color, Define::PixelShaderName::MODEL_DIFFUSE_SPLIT4COLOR);
    mEnemy.mModel->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse_Split4Color));
    mEnemy.mTransform = Utility::Transform(
        Math::Vector3(0, 0, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(1.0f, 1.0f, 1.0f));

    mTmp = std::make_unique<Tmp>();

    Math::Rect vpRect(0, 0, Define::Window::WIDTH, Define::Window::HEIGHT);
    mTmp->mRenderTargetViews = std::make_unique<Graphics::MultiRenderTarget>(mTmp->RTV_NUM, vpRect);

    mTmp->mRenderTargetViews->createDepthStencilView();
    mTmp->mRenderTargetViews->setClearColor(Graphics::Color4::WHITE);

    mTmp->mSprite = std::make_unique<Graphics::Sprite2D>(mTmp->mRenderTargetViews->getRenderTargetTexture(0));

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    blendDesc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAlignmentBlendDesc();
    blendDesc.RenderTarget[1] = Graphics::AlphaBlendSetting::getAlignmentBlendDesc();
    blendDesc.RenderTarget[2] = Graphics::AlphaBlendSetting::getAlignmentBlendDesc();
    blendDesc.RenderTarget[3] = Graphics::AlphaBlendSetting::getAlignmentBlendDesc();

    mTmp->mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(blendDesc);

    mUIWindow = std::make_unique<ImGUI::Window>("Output");
#define ADD_CHANGE_OUTPUT_COLOR_BUTTON(num) { \
            std::shared_ptr<ImGUI::Button> button = \
        std::make_shared<ImGUI::Button>(#num, [&]() { \
            mTmp->mSprite->setTexture(mTmp->mRenderTargetViews->getRenderTargetTexture(num), false); \
        }); \
        mUIWindow->addItem(button); \
        }

    ADD_CHANGE_OUTPUT_COLOR_BUTTON(0);
    ADD_CHANGE_OUTPUT_COLOR_BUTTON(1);
    ADD_CHANGE_OUTPUT_COLOR_BUTTON(2);
    ADD_CHANGE_OUTPUT_COLOR_BUTTON(3);
}

MultiRenderTargetTest::~MultiRenderTargetTest() {}

void MultiRenderTargetTest::load(Scene::Collecter& collecter) {}

void MultiRenderTargetTest::update(float delta) {}

bool MultiRenderTargetTest::isEndScene() const {
    return false;
}

void MultiRenderTargetTest::draw() {
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4::WHITE);
    mTmp->mAlphaBlend->set();
    //前のレンダーターゲットの保存
    ID3D11DepthStencilView* backDepthStencil;
    ID3D11RenderTargetView* backRenderTarget;
    UINT backRenderTargetNum = 1;
    D3D11_VIEWPORT backViewport;
    UINT backViewportNum = 1;
    Utility::getContext()->RSGetViewports(&backViewportNum, &backViewport);
    Utility::getContext()->OMGetRenderTargets(backRenderTargetNum, &backRenderTarget, &backDepthStencil);

    mTmp->mRenderTargetViews->set();
    mTmp->mRenderTargetViews->clear();


    mPerspectiveCamera->setMatrix();
    mEnemy.draw();

    //前の状態を復元
    Utility::getContext()->RSSetViewports(backViewportNum, &backViewport);
    Utility::getContext()->OMSetRenderTargets(backRenderTargetNum, &backRenderTarget, backDepthStencil);

    mOrthographicCamera->setMatrix();
    mTmp->mSprite->draw();

    backRenderTarget->Release();
    backDepthStencil->Release();
    mUIWindow->draw();
}

void MultiRenderTargetTest::end() {}

Define::SceneType MultiRenderTargetTest::next() {
    return Define::SceneType();
}

void MultiRenderTargetTest::GameObject::draw() {
    mModel->draw(mTransform);
}
