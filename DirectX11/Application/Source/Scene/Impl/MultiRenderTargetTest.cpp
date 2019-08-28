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
#include "Source/DefienClearColor.h"
#include "Framework/Utility/ImGUI/Button.h"

using namespace Framework;

namespace {
static constexpr int RTV_NUM = 4;
std::unique_ptr<Graphics::AlphaBlend> mAlphaBlend;
std::unique_ptr<Graphics::Sprite2D> mSprite;
std::array<ID3D11RenderTargetView*, RTV_NUM> mRenderTargetViews;
std::unique_ptr<Graphics::DepthStencilView> mDepthStencil;
std::array<std::shared_ptr<Graphics::Texture>, RTV_NUM> mRenderTargetTexs;
std::array<D3D11_VIEWPORT, RTV_NUM> mViewports;

auto CreateTestBlendDesc = []() {
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;
    ZeroMemory(&RenderTarget, sizeof(RenderTarget));
    RenderTarget.BlendEnable = FALSE;
    RenderTarget.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
    RenderTarget.DestBlend = D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
    RenderTarget.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    return RenderTarget;
};

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

    D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
    ZeroMemory(&viewDesc, sizeof(viewDesc));
    viewDesc.Format = texDesc.Format;
    viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    for (int i = 0; i < RTV_NUM; i++) {
        auto texBuffer = std::make_shared<Graphics::TextureBuffer>(texDesc);
        HRESULT hr = Utility::getDevice()->CreateRenderTargetView(texBuffer->getBuffer().Get(), &viewDesc, &mRenderTargetViews[i]);
        MY_ASSERTION(SUCCEEDED(hr), "");
        auto srv = std::make_shared<Graphics::ShaderResourceView>(*texBuffer, nullptr);
        mRenderTargetTexs[i] = std::make_shared<Graphics::Texture>(
            texBuffer,
            srv,
            texDesc.Width,
            texDesc.Height);
        mViewports[i].TopLeftX = 0;
        mViewports[i].TopLeftY = 0;
        mViewports[i].Width = texDesc.Width;
        mViewports[i].Height = texDesc.Height;
        mViewports[i].MinDepth = 0;
        mViewports[i].MaxDepth = 1.0;
    }


    D3D11_TEXTURE2D_DESC depthTexDesc;
    ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
    depthTexDesc.Width = texDesc.Width;
    depthTexDesc.Height = texDesc.Height;
    depthTexDesc.MipLevels = 1;
    depthTexDesc.ArraySize = 1;
    depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthTexDesc.SampleDesc.Count = 1;
    depthTexDesc.SampleDesc.Quality = 0;
    depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
    depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthTexDesc.CPUAccessFlags = 0;
    depthTexDesc.MiscFlags = 0;

    D3D11_DEPTH_STENCIL_VIEW_DESC dsd;
    ZeroMemory(&dsd, sizeof(dsd));
    dsd.Format = depthTexDesc.Format;
    dsd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsd.Texture2D.MipSlice = 0;
    mDepthStencil = std::make_unique<Graphics::DepthStencilView>(depthTexDesc, dsd);

    mSprite = std::make_unique<Graphics::Sprite2D>(mRenderTargetTexs[0]);

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    blendDesc.RenderTarget[0] = CreateTestBlendDesc();
    blendDesc.RenderTarget[1] = CreateTestBlendDesc();
    blendDesc.RenderTarget[2] = CreateTestBlendDesc();
    blendDesc.RenderTarget[3] = CreateTestBlendDesc();

    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(blendDesc);

    mUIWindow = std::make_unique<ImGUI::Window>("Output");
#define ADD_CHANGE_OUTPUT_COLOR_BUTTON(num) { \
        std::shared_ptr<ImGUI::Button> button = \
    std::make_shared<ImGUI::Button>(#num, [&]() { \
        mSprite->setTexture(mRenderTargetTexs[num], false); \
    }); \
    mUIWindow->addItem(button); \
    }

    ADD_CHANGE_OUTPUT_COLOR_BUTTON(0);
    ADD_CHANGE_OUTPUT_COLOR_BUTTON(1);
    ADD_CHANGE_OUTPUT_COLOR_BUTTON(2);
    ADD_CHANGE_OUTPUT_COLOR_BUTTON(3);
}

MultiRenderTargetTest::~MultiRenderTargetTest() {
    for (int i = 0; i < RTV_NUM; i++) mRenderTargetViews[i]->Release();
}

void MultiRenderTargetTest::load(Scene::Collecter& collecter) {}

void MultiRenderTargetTest::update(float delta) {}

bool MultiRenderTargetTest::isEndScene() const {
    return false;
}

void MultiRenderTargetTest::draw() {
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4::WHITE);
    mAlphaBlend->set();
    //前のレンダーターゲットの保存
    ID3D11DepthStencilView* backDepthStencil;
    ID3D11RenderTargetView* backRenderTarget;
    UINT backRenderTargetNum = 1;
    D3D11_VIEWPORT backViewport;
    UINT backViewportNum = 1;
    Utility::getContext()->RSGetViewports(&backViewportNum, &backViewport);
    Utility::getContext()->OMGetRenderTargets(backRenderTargetNum, &backRenderTarget, &backDepthStencil);

    Utility::getContext()->RSSetViewports(RTV_NUM, mViewports.data());
    Utility::getContext()->OMSetRenderTargets(RTV_NUM, mRenderTargetViews.data(), mDepthStencil->getDepthStencilView().Get());
    for (int i = 0; i < RTV_NUM; i++) {
        constexpr float c[4]{ 1.0f,1.0f,1.0f,1.0f };
        Utility::getContext()->ClearRenderTargetView(mRenderTargetViews[i], c);
    }

    mDepthStencil->clear();

    mPerspectiveCamera->setMatrix();
    mEnemy.draw();

    //前の状態を復元
    Utility::getContext()->RSSetViewports(backViewportNum, &backViewport);
    Utility::getContext()->OMSetRenderTargets(backRenderTargetNum, &backRenderTarget, backDepthStencil);

    mOrthographicCamera->setMatrix();
    mSprite->draw();

    mUIWindow->draw();
}

void MultiRenderTargetTest::end() {}

Define::SceneType MultiRenderTargetTest::next() {
    return Define::SceneType();
}

void MultiRenderTargetTest::GameObject::draw() {
    mModel->draw(mTransform);
}
