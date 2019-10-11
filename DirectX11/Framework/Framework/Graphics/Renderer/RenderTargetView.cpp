#include "RenderTargetView.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

RenderTargetView::RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Color4& backColor)
    :mBackColor(backColor) {
    mRenderTargetView.resize(1);
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture->getTexture().Get(), desc, &mRenderTargetView[0]));
}

RenderTargetView::RenderTargetView(std::vector<std::shared_ptr<Texture2D>> textures, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Color4 & backColor) {
    const UINT size = static_cast<UINT>(textures.size());
    mRenderTargetView.resize(size);
    for (UINT n = 0; n < size; n++) {
        throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(textures[n]->getTexture().Get(), desc, &mRenderTargetView[n]));
    }
}

RenderTargetView::RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
    std::shared_ptr<Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc, const Color4& backColor) {
    mRenderTargetView.resize(1);
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture->getTexture().Get(), desc, &mRenderTargetView[0]));
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(depthStencilTexture->getTexture().Get(), dsvDesc, &mDepthStencilView));
}

RenderTargetView::RenderTargetView(std::vector<std::shared_ptr<Texture2D>> textures, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
    std::shared_ptr<Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc, const Color4& backColor) {
    const UINT size = static_cast<UINT>(textures.size());
    mRenderTargetView.resize(size);
    for (UINT n = 0; n < size; n++) {
        throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(textures[n]->getTexture().Get(), desc, &mRenderTargetView[n]));
    }
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(depthStencilTexture->getTexture().Get(), dsvDesc, &mDepthStencilView));
}

RenderTargetView::~RenderTargetView() { }

void RenderTargetView::clear() {
    for (auto&& rtv : mRenderTargetView) {
        DX11InterfaceAccessor::getContext()->ClearRenderTargetView(rtv.Get(), mBackColor.get().data());
    }
    if (mDepthStencilView) {
        DX11InterfaceAccessor::getContext()->ClearDepthStencilView(mDepthStencilView.Get(),
            D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);
    }
}

void RenderTargetView::set() {
    const UINT size = static_cast<UINT>(mRenderTargetView.size());
    if (mDepthStencilView) {
        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(size, mRenderTargetView[0].GetAddressOf(), mDepthStencilView.Get());
    }
    else {
        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(size, mRenderTargetView[0].GetAddressOf(), nullptr);
    }
}

void RenderTargetView::end() {
    ID3D11RenderTargetView* const view[] = { nullptr };
    DX11InterfaceAccessor::getContext()->OMSetRenderTargets(_countof(view), view, nullptr);
}

ComPtr<ID3D11RenderTargetView> RenderTargetView::getRenderTargetView(UINT n) const {
    MY_ASSERTION(n < mRenderTargetView.size(), "�z��͈̔͊O�ł�");
    return mRenderTargetView[n];
}

} //Graphics 
} //Framework 