#include "RenderingManager.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/ImGUI/Manager.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Graphics/Render/RenderTargetView.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Render/Viewport.h"

namespace {
Framework::Graphics::RenderTargetView* view;
Framework::Graphics::Viewport* viewport;
}
namespace Framework {
namespace Graphics {

RenderingManager::RenderingManager(HWND hWnd, const Math::Vector2& screenSize, bool isFullScreen)
    :mScreenSize(screenSize), mGraphicsDevice(std::make_unique<GraphicsDevice>(hWnd, screenSize, isFullScreen)),
    mConstantBufferManager(nullptr) {}

RenderingManager::~RenderingManager() {
    if (view)delete view;
    if (viewport)delete viewport;
}

void RenderingManager::initialize() {
    mConstantBufferManager = std::make_unique<ConstantBufferManager>();
    mImGUIManager = std::make_unique<ImGUI::Manager>();

    view = new RenderTargetView(mGraphicsDevice->getDirectX11GraphicsDevice()->getBackBuffer()->getBuffer().Get());
    viewport = new Viewport(Math::Rect(0.0f, 0.0f, mScreenSize.x, mScreenSize.y));

    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = 800;
    desc.Height = 600;
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
}

void RenderingManager::drawBegin() {
    mGraphicsDevice->drawBegin();
    view->clear(Color4(0.7f, 0.7f, 0.7f, 1.0f));
    view->set();
    viewport->set();
}

void RenderingManager::drawEnd() {
    mImGUIManager->drawAll();

    //•`‰æ‚ÌÅIˆ—‚ðs‚¤ 
    mGraphicsDevice->drawEnd();
}

} //Graphics 
} //Framework 