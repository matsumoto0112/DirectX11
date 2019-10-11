//#include "RenderTarget.h"
//#include "Framework/Graphics/Render/DepthStencilView.h"
//#include "Framework/Graphics/Render/RenderTargetView.h"
//#include "Framework/Graphics/Shader/ShaderResourceView.h"
//#include "Framework/Graphics/Texture/Texture.h"
//#include "Framework/Graphics/Texture/TextureBuffer.h"
//#include "Framework/Utility/Debug.h"
//#include "Framework/Graphics/DX11InterfaceAccessor.h"
//
//namespace {
//using UINTPair = std::pair<UINT, UINT>;
//UINTPair getTextureSize(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) {
//    ID3D11Texture2D* texture;
//    rtv->GetResource((ID3D11Resource**)&texture);
//    D3D11_TEXTURE2D_DESC texDesc;
//    texture->GetDesc(&texDesc);
//    UINTPair res(texDesc.Width, texDesc.Height);
//    texture->Release();
//    return res;
//}
//}
//
//namespace Framework {
//namespace Graphics {
//
//RenderTarget::RenderTarget(TextureBufferPtr texture,
//    ViewportPtr viewport,
//    SRVFlag useSRV)
//    :mRenderTargetView(std::make_unique<RenderTargetView>(texture)),
//    mDepthStencilView(nullptr),
//    mTexture(nullptr),
//    mViewport(std::move(viewport)),
//    mEnableDepthStencil(false),
//    mClearColor(Color4::WHITE) {
//    if (useSRV == SRVFlag::Use) {
//        std::shared_ptr<ShaderResourceView> srv = std::make_shared<ShaderResourceView>(*texture, nullptr);
//        mTexture = std::make_shared<Texture>(texture, srv);
//    }
//}
//
//RenderTarget::RenderTarget(TextureBufferPtr texture,
//    const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc,
//    ViewportPtr viewport,
//    SRVFlag useSRV)
//    : mRenderTargetView(std::make_unique<RenderTargetView>(texture, rtvDesc)),
//    mDepthStencilView(nullptr),
//    mViewport(std::move(viewport)),
//    mEnableDepthStencil(false),
//    mClearColor(Color4::WHITE) {
//    if (useSRV == SRVFlag::Use) {
//        std::shared_ptr<ShaderResourceView> srv = std::make_shared<ShaderResourceView>(*texture, nullptr);
//        mTexture = std::make_shared<Texture>(texture, srv);
//    }
//}
//
//RenderTarget::~RenderTarget() {}
//
//void RenderTarget::createDepthStencilView() {
//    const UINTPair size = getTextureSize(mRenderTargetView->getRenderTargetView());
//    mDepthStencilView = std::make_unique<DepthStencilView>(size.first, size.second);
//    mEnableDepthStencil = true;
//}
//
//void RenderTarget::createDepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc,
//    const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc) {
//    mDepthStencilView = std::make_unique<DepthStencilView>(texDesc, dsvDesc);
//    mEnableDepthStencil = true;
//}
//
//void RenderTarget::set() {
//    if (mEnableDepthStencil) {
//        MY_ASSERTION(mDepthStencilView != nullptr, "深度・ステンシルビューが未作成です");
//        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(1,
//            mRenderTargetView->getRenderTargetView().GetAddressOf(),
//            mDepthStencilView->getDepthStencilView().Get());
//    }
//    else {
//        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(1,
//            mRenderTargetView->getRenderTargetView().GetAddressOf(),
//            nullptr);
//    }
//    mViewport->set();
//}
//
//void RenderTarget::reset() {
//    ID3D11RenderTargetView* rtv[1]{ nullptr };
//    DX11InterfaceAccessor::getContext()->OMSetRenderTargets(1, rtv, nullptr);
//}
//
//void RenderTarget::clear() {
//    mRenderTargetView->clear(mClearColor);
//    if (mEnableDepthStencil && mDepthStencilView) {
//        mDepthStencilView->clear();
//    }
//}
//
//RenderTarget::TexturePtr RenderTarget::getRenderTargetTexture() {
//    return mTexture;
//}
//
//} //Graphics 
//} //Framework 
