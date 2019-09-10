#include "RenderingManager.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Graphics/ImGUI/Manager.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Render/Viewport.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"

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

    mRenderTarget = std::make_unique<RenderTarget>(
        mGraphicsDevice->getDirectX11GraphicsDevice()->getBackBuffer(),
        std::make_unique<Viewport>(Math::Rect(0.0f, 0.0f, mScreenSize.x, mScreenSize.y)),
        SRVFlag::NoUse);
    mRenderTarget->createDepthStencilView(
        Graphics::DepthStencilDesc::getDefaultTexture2DDesc(
            static_cast<UINT>(mScreenSize.x),
            static_cast<UINT>(mScreenSize.y)),
        DepthStencilDesc::getDefaultDepthStencilViewDesc());

    mDefaultSampler = std::make_unique<Sampler>(TextureAddressMode::Wrap, TextureFilterMode::MinMagMipLinear);
}

void RenderingManager::changeRenderTargetColor(const Color4& color) {
    mRenderTarget->setClearColor(color);
}

void RenderingManager::drawBegin() {
    mGraphicsDevice->drawBegin();
    mRenderTarget->clear();
    mRenderTarget->set();
    mDefaultSampler->setData(ShaderInputType::Pixel, 0);
}

void RenderingManager::drawEnd() {
    mImGUIManager->drawAll();
    mLightManager->set();

    //•`‰æ‚ÌÅIˆ—‚ðs‚¤ 
    mGraphicsDevice->drawEnd();
}

void RenderingManager::setBackbuffer() {
    mRenderTarget->clear();
    mRenderTarget->set();
}

} //Graphics 
} //Framework 