#include "DepthStencilView.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

DepthStencilView::DepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc,
    const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc) {
    HRESULT hr = Utility::getDevice()->CreateTexture2D(&texDesc, nullptr, &mTexture);
    MY_ASSERTION(SUCCEEDED(hr), "DepthStencil—pTexture2Dì¬Ž¸”s");
    hr = Utility::getDevice()->CreateDepthStencilView(mTexture.Get(), &dsvDesc, &mDepthStencil);
    MY_ASSERTION(SUCCEEDED(hr), "DepthStencilì¬Ž¸”s");
}

DepthStencilView::DepthStencilView(UINT width, UINT height) {
    HRESULT hr = Utility::getDevice()->CreateTexture2D(&DepthStencilDesc::getDefaultTexture2DDesc(width, height), nullptr, &mTexture);
    MY_ASSERTION(SUCCEEDED(hr), "DepthStencil—pTexture2Dì¬Ž¸”s");
    hr = Utility::getDevice()->CreateDepthStencilView(mTexture.Get(), &DepthStencilDesc::getDefaultDepthStencilViewDesc(), &mDepthStencil);
    MY_ASSERTION(SUCCEEDED(hr), "DepthStencilì¬Ž¸”s");
}

DepthStencilView::~DepthStencilView() {}

void DepthStencilView::clear() {
    Utility::getContext()->ClearDepthStencilView(mDepthStencil.Get(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

} //Graphics 
} //Framework 
