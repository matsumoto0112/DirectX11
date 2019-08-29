#include "RenderTarget.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Graphics/Render/RenderTargetView.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

RenderTarget::RenderTarget(TexturePtr texture)
    :mRenderTargetView(std::make_unique<RenderTargetView>(texture)),
    mDepthStencilView(nullptr),
    mUseDepthStencil(false),
    mClearColor(Color4::WHITE) {}

RenderTarget::RenderTarget(TexturePtr texture,
    const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc)
    : mRenderTargetView(std::make_unique<RenderTargetView>(texture, rtvDesc)) {}

RenderTarget::~RenderTarget() {}

void RenderTarget::bindDepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc,
    const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc) {
    mDepthStencilView = std::make_unique<DepthStencilView>(texDesc, dsvDesc);
    mUseDepthStencil = true;
}

void RenderTarget::set() {
    if (mUseDepthStencil) {
        MY_ASSERTION(mDepthStencilView != nullptr, "深度・ステンシルビューが未作成です");
        Utility::getContext()->OMSetRenderTargets(1,
            mRenderTargetView->getRenderTargetView().GetAddressOf(),
            mDepthStencilView->getDepthStencilView().Get());
    }
    else {
        Utility::getContext()->OMSetRenderTargets(1,
            mRenderTargetView->getRenderTargetView().GetAddressOf(),
            nullptr);
    }
}

void RenderTarget::clear() {
    mRenderTargetView->clear(mClearColor);
    if (mUseDepthStencil && mDepthStencilView) {
        mDepthStencilView->clear();
    }
}

} //Graphics 
} //Framework 
