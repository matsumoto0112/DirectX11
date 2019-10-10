#include "RenderTargetView.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

RenderTargetView::RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Color4& backColor)
    :mBackColor(backColor) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture->getTexture().Get(), desc, &mRenderTargetView));
}

RenderTargetView::~RenderTargetView() { }

void RenderTargetView::clear() {
    DX11InterfaceAccessor::getContext()->ClearRenderTargetView(mRenderTargetView.Get(), mBackColor.get().data());
}

void RenderTargetView::set() {
    DX11InterfaceAccessor::getContext()->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
}

} //Graphics 
} //Framework 
