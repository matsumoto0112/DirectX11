#include "RenderTargetView.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

RenderTargetView::RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
    const Viewport& viewport, const Color4& backColor)
    : mViewport(viewport), mBackColor(backColor), mEnableDepthStencil(false) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture->getTexture().Get(), desc, &mRenderTargetView));
}

RenderTargetView::RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
    std::shared_ptr<Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc,
    const Viewport& viewport, const Color4& backColor)
    : mViewport(viewport), mBackColor(backColor), mEnableDepthStencil(true) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture->getTexture().Get(), desc, &mRenderTargetView));
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(depthStencilTexture->getTexture().Get(), dsvDesc, &mDepthStencilView));
}

RenderTargetView::~RenderTargetView() { }

void RenderTargetView::clear() {
    DX11InterfaceAccessor::getContext()->ClearRenderTargetView(mRenderTargetView.Get(), mBackColor.get().data());
    if (mDepthStencilView && mEnableDepthStencil) {
        DX11InterfaceAccessor::getContext()->ClearDepthStencilView(mDepthStencilView.Get(),
            D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);
    }
}

void RenderTargetView::set() {
    mViewport.set();
    if (mDepthStencilView && mEnableDepthStencil) {
        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
    }
    else {
        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
    }
}

void RenderTargetView::end() {
    ID3D11RenderTargetView* const view[] = { nullptr };
    DX11InterfaceAccessor::getContext()->OMSetRenderTargets(ARRAYSIZE(view), view, nullptr);
}

ComPtr<ID3D11RenderTargetView> RenderTargetView::getRenderTargetView() const {
    return mRenderTargetView;
}

} //Graphics 
} //Framework 
