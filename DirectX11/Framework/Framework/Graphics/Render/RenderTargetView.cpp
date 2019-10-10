#include "RenderTargetView.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

RenderTargetView::RenderTargetView(TexturePtr texture) {
    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture->getBuffer().Get(), nullptr, &mRenderTargetView);
    MY_ERROR_WINDOW(SUCCEEDED(hr), "‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

RenderTargetView::RenderTargetView(TexturePtr texture,
    const D3D11_RENDER_TARGET_VIEW_DESC& desc) {
    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture->getBuffer().Get(), &desc, &mRenderTargetView);
    MY_ERROR_WINDOW(SUCCEEDED(hr), "‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

RenderTargetView::~RenderTargetView() {}

void RenderTargetView::clear(const Color4& clearColor) {
    DX11InterfaceAccessor::getContext()->ClearRenderTargetView(mRenderTargetView.Get(), clearColor.get().data());
}

} //Graphics 
} //Framework 
