#include "RenderingManager.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Graphics/ImGUI/Manager.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Render/Viewport.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Render/RTVWithDSV.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"

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

    std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(mGraphicsDevice->getDirectX11GraphicsDevice()->getBackBuffer());
    std::shared_ptr<RenderTargetView> renderTarget = std::make_shared<RenderTargetView>(texture, nullptr, Color4::WHITE);

    D3D11_BLEND_DESC desc{};
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    for (int i = 0; i < 8; i++) {
        desc.RenderTarget[i] = AlphaBlendSetting::getDefaultDesc();
    }
    std::shared_ptr<AlphaBlend> blendState = std::make_shared<AlphaBlend>(desc);
    mDefaultPipeline = std::make_unique<Pipeline>(renderTarget, blendState);
}

Pipeline* RenderingManager::drawBegin() {
    mGraphicsDevice->drawBegin();
    mDefaultPipeline->begin();
    mDefaultSampler->setData(ShaderInputType::Pixel, 0);
    return mDefaultPipeline.get();
}

void RenderingManager::drawEnd() {
    mImGUIManager->drawAll();

    //描画の最終処理を行う 
    mGraphicsDevice->drawEnd();
}

} //Graphics 
} //Framework 