#include "RenderingManager.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/ImGUI/Manager.h"

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
}

void RenderingManager::drawBegin() {
    mGraphicsDevice->drawBegin();
    view->clear(Color4(1.0f, 0.0f, 0.0f, 1.0f));
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