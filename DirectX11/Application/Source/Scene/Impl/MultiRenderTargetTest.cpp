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
#include "Framework/Graphics/Desc/DepthStencil.h"
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

    //Z値を格納するテクスチャを作成する
    D3D11_TEXTURE2D_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(texDesc));
    texDesc.Width = Define::Window::WIDTH;
    texDesc.Height = Define::Window::HEIGHT;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
    texDesc.CPUAccessFlags = 0;

    mTmp = std::make_unique<Tmp>();

    D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
    ZeroMemory(&viewDesc, sizeof(viewDesc));
    viewDesc.Format = texDesc.Format;
    viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    std::vector<std::shared_ptr<Graphics::TextureBuffer>> texBufs;
    for (int i = 0; i < mTmp->RTV_NUM; i++) {
        auto texBuffer = std::make_shared<Graphics::TextureBuffer>(texDesc);
        texBufs.emplace_back(texBuffer);
    }

    Math::Rect vpRect(0, 0, texDesc.Width, texDesc.Height);
    mTmp->mRenderTargetViews = std::make_unique<Graphics::MultiRenderTarget>(
        mTmp->RTV_NUM,
        texBufs,
        viewDesc,
        vpRect);

    mTmp->mRenderTargetViews->bindDepthStencilView(
        Graphics::DepthStencilDesc::getDefaultTexture2DDesc(texDesc.Width, texDesc.Height),
        Graphics::DepthStencilDesc::getDefaultDepthStencilViewDesc());
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
