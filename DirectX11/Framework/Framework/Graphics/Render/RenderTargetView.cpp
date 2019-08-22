#include "RenderTargetView.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

RenderTargetView::RenderTargetView(ID3D11Resource* resource) {
    HRESULT hr = Utility::getDevice()->CreateRenderTargetView(resource, nullptr, &mRenderTargetView);
    MY_ERROR_WINDOW(SUCCEEDED(hr), "�������Ɏ��s���܂���");
}

RenderTargetView::RenderTargetView(ID3D11Resource* resource, const D3D11_RENDER_TARGET_VIEW_DESC& desc) {
    HRESULT hr = Utility::getDevice()->CreateRenderTargetView(resource, &desc, &mRenderTargetView);
    MY_ERROR_WINDOW(SUCCEEDED(hr), "�������Ɏ��s���܂���");
}

RenderTargetView::~RenderTargetView() {}

void RenderTargetView::set() {
    if (mDepthStencil) {
        Utility::getContext()->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencil->getDepthStencilView().Get());
    }
    else {
        Utility::getContext()->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
    }
}

void RenderTargetView::clear(const Color4& clearColor) {
    Utility::getContext()->ClearRenderTargetView(mRenderTargetView.Get(), clearColor.get().data());
    if (mDepthStencil) {
        mDepthStencil->clear();
    }
}

} //Graphics 
} //Framework 
