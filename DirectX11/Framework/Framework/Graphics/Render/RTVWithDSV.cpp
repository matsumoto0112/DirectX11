#include "RTVWithDSV.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

RTVWithDSV::RTVWithDSV(ComPtr<ID3D11Texture2D> renderTargetTexture, const D3D11_RENDER_TARGET_VIEW_DESC* rtvDesc,
    ComPtr<ID3D11Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(renderTargetTexture.Get(), rtvDesc, &mRenderTargetView));
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(depthStencilTexture.Get(), dsvDesc, &mDepthStencilView));
}
RTVWithDSV::~RTVWithDSV() { }

void RTVWithDSV::clear() {
    DX11InterfaceAccessor::getContext()->ClearRenderTargetView(mRenderTargetView.Get(), mBackColor.get().data());
    DX11InterfaceAccessor::getContext()->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void RTVWithDSV::set() {
    DX11InterfaceAccessor::getContext()->OMGetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.GetAddressOf());
}

} //Graphics 
} //Framework 
