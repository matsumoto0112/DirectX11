#include "RenderTargetView.h"
#include "Utility/Debug.h"
#include "Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

RenderTargetView::RenderTargetView(ID3D11Resource* resource) {
    HRESULT hr = Utility::getDevice()->CreateRenderTargetView(resource, nullptr, &mRenderTargetView);
    MY_ERROR_WINDOW(SUCCEEDED(hr), "‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

RenderTargetView::RenderTargetView(ID3D11Resource* resource, D3D11_RENDER_TARGET_VIEW_DESC* desc) {
    HRESULT hr = Utility::getDevice()->CreateRenderTargetView(resource, desc, &mRenderTargetView);
    MY_ERROR_WINDOW(SUCCEEDED(hr), "‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

RenderTargetView::~RenderTargetView() {}

void RenderTargetView::set() {
    Utility::getContext()->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
}

void RenderTargetView::clear(const Color4& clearColor) {
    Utility::getContext()->ClearRenderTargetView(mRenderTargetView.Get(), clearColor.get().data());
}

} //Graphics 
} //Framework 
