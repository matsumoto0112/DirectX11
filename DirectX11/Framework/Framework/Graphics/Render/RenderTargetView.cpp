#include "RenderTargetView.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

RenderTargetView::RenderTargetView(Microsoft::WRL::ComPtr<ID3D11Resource> resource) {
    HRESULT hr = Utility::getDevice()->CreateRenderTargetView(resource.Get(), nullptr, &mRenderTargetView);
    MY_ERROR_WINDOW(SUCCEEDED(hr), "èâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩ");
}

RenderTargetView::RenderTargetView(Microsoft::WRL::ComPtr<ID3D11Resource> resource, const D3D11_RENDER_TARGET_VIEW_DESC& desc) {
    HRESULT hr = Utility::getDevice()->CreateRenderTargetView(resource.Get(), &desc, &mRenderTargetView);
    MY_ERROR_WINDOW(SUCCEEDED(hr), "èâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩ");
}

RenderTargetView::~RenderTargetView() {}

void RenderTargetView::clear(const Color4& clearColor) {
    Utility::getContext()->ClearRenderTargetView(mRenderTargetView.Get(), clearColor.get().data());
}

} //Graphics 
} //Framework 
