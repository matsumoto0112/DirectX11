#include "RenderingManager.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/Renderer/Viewport.h"
#include "Framework/Graphics/Texture/Sampler.h"

namespace Framework {
namespace Graphics {

RenderingManager::RenderingManager(HWND hWnd, UINT width, UINT height, bool isFullScreen)
    :mWidth(width), mHeight(height), mGraphicsDevice(std::make_unique<GraphicsDevice>(hWnd, width, height, isFullScreen)),
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
        mWidth, mHeight, Color4::BLACK);
}

IRenderer* RenderingManager::drawBegin() {
    mGraphicsDevice->drawBegin();
    mBackBufferRenderer->begin();
    mDefaultSampler->setData(ShaderInputType::Pixel, 0);
    return mBackBufferRenderer.get();
}

void RenderingManager::drawEnd() {
    mImGUIManager->drawAll();
    
    //�o�b�N�o�b�t�@�̕`����I����
    mBackBufferRenderer->end();

    //�`��̍ŏI�������s�� 
    mGraphicsDevice->drawEnd();

    //�R���e�L�X�g�̏����N���A����
    DX11InterfaceAccessor::getContext()->ClearState();
    DX11InterfaceAccessor::getContext()->Flush();
}

} //Graphics 
} //Framework 