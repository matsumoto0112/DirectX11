#include "DepthStencilView.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

DepthStencilView::DepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc,
    const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc) {
    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateTexture2D(&texDesc, nullptr, &mTexture);
    MY_ASSERTION(SUCCEEDED(hr), "DepthStencil用Texture2D作成失敗");
    hr = DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(mTexture.Get(), &dsvDesc, &mDepthStencil);
    MY_ASSERTION(SUCCEEDED(hr), "DepthStencil作成失敗");
}

DepthStencilView::DepthStencilView(UINT width, UINT height) {
    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateTexture2D(&DepthStencilDesc::getDefaultTexture2DDesc(width, height), nullptr, &mTexture);
    MY_ASSERTION(SUCCEEDED(hr), "DepthStencil用Texture2D作成失敗");
    hr = DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(mTexture.Get(), &DepthStencilDesc::getDefaultDepthStencilViewDesc(), &mDepthStencil);
    MY_ASSERTION(SUCCEEDED(hr), "DepthStencil作成失敗");
}

DepthStencilView::~DepthStencilView() {}

void DepthStencilView::clear() {
    DX11InterfaceAccessor::getContext()->ClearDepthStencilView(mDepthStencil.Get(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

} //Graphics 
} //Framework 
