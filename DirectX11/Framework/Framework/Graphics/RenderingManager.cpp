#include "RenderingManager.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/ImGUI/Manager.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Render/Viewport.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Define/Desc/DepthStencil.h"
#include "Framework/Define/Window.h"

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

    mRenderTarget = std::make_unique<RenderTarget>(mGraphicsDevice->getDirectX11GraphicsDevice()->getBackBuffer());
    mRenderTarget->bindDepthStencilView(
        Define::DepthStencilDesc::getDefaultTexture2DDesc(
            static_cast<UINT>(mScreenSize.x),
            static_cast<UINT>(mScreenSize.y)),
        Define::DepthStencilDesc::getDefaultDepthStencilViewDesc());
    mViewport = std::make_unique<Viewport>(Math::Rect(0.0f, 0.0f, mScreenSize.x, mScreenSize.y));

    mDefaultSampler = std::make_unique<Sampler>(TextureAddressMode::Wrap, TextureFilterMode::MinMagMipLinear);
}

void RenderingManager::drawBegin(const Color4& clearColor) {
    mGraphicsDevice->drawBegin();
    mRenderTarget->setClearColor(clearColor);
    mRenderTarget->clear();
    mRenderTarget->set();
    mViewport->set();
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