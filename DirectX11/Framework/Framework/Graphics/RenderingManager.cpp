#include "RenderingManager.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Graphics/ImGUI/Manager.h"
#include "Framework/Graphics/Renderer/AlphaBlend.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Renderer/Viewport.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Renderer/RTVWithDSV.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"

namespace Framework {
namespace Graphics {

RenderingManager::RenderingManager(HWND hWnd, const Math::Vector2& screenSize, bool isFullScreen)
    :mScreenSize(screenSize), mGraphicsDevice(std::make_unique<GraphicsDevice>(hWnd, screenSize, isFullScreen)),
    mConstantBufferManager(nullptr),
    mCameraManager(nullptr) { }

RenderingManager::~RenderingManager() { }

void RenderingManager::initialize() {
    mConstantBufferManager = std::make_unique<ConstantBufferManager>();
    mCameraManager = std::make_unique<CameraManager>();
    mImGUIManager = std::make_unique<ImGUI::Manager>();

    mDefaultSampler = std::make_unique<Sampler>(TextureAddressMode::Wrap, TextureFilterMode::MinMagMipLinear);

    mBackBufferRenderer = std::make_unique<BackBufferRenderer>(
        std::make_shared<Texture2D>(mGraphicsDevice->getDirectX11GraphicsDevice()->getBackBuffer()),
        mScreenSize.x, mScreenSize.y, Color4::WHITE);
    //std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(
    //    mGraphicsDevice->getDirectX11GraphicsDevice()->getBackBuffer());
    //std::shared_ptr<Texture2D> dsvTexture = std::make_shared<Texture2D>(
    //    &DepthStencilDesc::getMSAATexture2DDesc(mScreenSize.x, mScreenSize.y), nullptr);
    //std::shared_ptr<RenderTargetView> renderTarget = std::make_shared<RenderTargetView>(texture, nullptr,
    //    dsvTexture, &DepthStencilDesc::getMSAADepthStencilViewDesc(), Color4::WHITE);
    //std::shared_ptr<RenderTargetView> renderTarget = std::make_shared<RenderTargetView>(texture, nullptr, Color4::WHITE);
    //std::shared_ptr<AlphaBlend> blendState = std::make_shared<AlphaBlend>(Graphics::BlendStateDesc::BLEND_DESC(Graphics::AlphaBlendType::Default));
    //Viewport viewport(Math::Rect(0, 0, mScreenSize.x, mScreenSize.y));
}

IRenderer* RenderingManager::drawBegin() {
    mGraphicsDevice->drawBegin();
    mBackBufferRenderer->begin();
    mDefaultSampler->setData(ShaderInputType::Pixel, 0);
    return mBackBufferRenderer.get();
}

void RenderingManager::drawEnd() {
    mImGUIManager->drawAll();
    mBackBufferRenderer->end();
    //•`‰æ‚ÌÅIˆ—‚ðs‚¤ 
    mGraphicsDevice->drawEnd();
}

} //Graphics 
} //Framework 