#include "DepthStencilView.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

DepthStencilView::DepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc,
    const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateTexture2D(&texDesc, nullptr, &mTexture));
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(mTexture.Get(), &dsvDesc, &mDepthStencil));
}

DepthStencilView::DepthStencilView(UINT width, UINT height) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateTexture2D(&DepthStencilDesc::getDefaultTexture2DDesc(width, height), nullptr, &mTexture));
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(mTexture.Get(), &DepthStencilDesc::getDefaultDepthStencilViewDesc(), &mDepthStencil));
}

DepthStencilView::~DepthStencilView() { }

void DepthStencilView::clear() {
    DX11InterfaceAccessor::getContext()->ClearDepthStencilView(mDepthStencil.Get(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

} //Graphics 
} //Framework 
