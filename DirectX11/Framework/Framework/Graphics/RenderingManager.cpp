#include "stdafx.h"
#include "RenderingManager.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/ImGUI/Manager.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Graphics/Render/RenderTargetView.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Render/Viewport.h"

#include "Source/DefienClearColor.h"

namespace {
std::unique_ptr<Framework::Graphics::RenderTargetView> view;
std::unique_ptr<Framework::Graphics::Viewport> viewport;
std::unique_ptr<Framework::Graphics::Sampler> mDefaultSampler;
}
namespace Framework {
namespace Graphics {

RenderingManager::RenderingManager(HWND hWnd, const Math::Vector2& screenSize, bool isFullScreen)
    :mScreenSize(screenSize), mGraphicsDevice(std::make_unique<GraphicsDevice>(hWnd, screenSize, isFullScreen)),
    mConstantBufferManager(nullptr) {}

RenderingManager::~RenderingManager() {}

void RenderingManager::initialize() {
    mConstantBufferManager = std::make_unique<ConstantBufferManager>();
    mLightManager = std::make_unique<LightManager>();
    mImGUIManager = std::make_unique<ImGUI::Manager>();

    view = std::make_unique<RenderTargetView>(mGraphicsDevice->getDirectX11GraphicsDevice()->getBackBuffer()->getBuffer());
    viewport = std::make_unique<Viewport>(Math::Rect(0.0f, 0.0f, mScreenSize.x, mScreenSize.y));

    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = Define::Window::WIDTH;
    desc.Height = Define::Window::HEIGHT;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    D3D11_DEPTH_STENCIL_VIEW_DESC ds;
    ZeroMemory(&ds, sizeof(ds));
    ds.Format = desc.Format;
    ds.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    ds.Texture2D.MipSlice = 0;
    view->setDepthStencilView(std::make_unique<DepthStencilView>(desc, ds));

    mDefaultSampler = std::make_unique<Sampler>(TextureAddressMode::Wrap, TextureFilterMode::MinMagMipLinear);
}

void RenderingManager::drawBegin() {
    mGraphicsDevice->drawBegin();
    view->clear(ClearRenderTargetColor);
    view->set();
    viewport->set();
    mDefaultSampler->setData(ShaderInputType::Pixel, 0);
}

void RenderingManager::drawEnd() {
    mImGUIManager->drawAll();
    mLightManager->set();

    //描画の最終処理を行う 
    mGraphicsDevice->drawEnd();
}

} //Graphics 
} //Framework 