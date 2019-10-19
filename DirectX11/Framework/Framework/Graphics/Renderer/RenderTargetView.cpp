#include "RenderTargetView.h"
//#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
    namespace Graphics {

        RenderTargetView::RenderTargetView(ID3D11Device* device, std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
            const Viewport& viewport, const Color4& backColor)
            : mViewport(viewport), mBackColor(backColor), mEnableDepthStencil(false) {
            throwIfFailed(device->CreateRenderTargetView(texture->getTexture().Get(), desc, &mRenderTargetView));
        }

        RenderTargetView::RenderTargetView(ID3D11Device* device, std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
            std::shared_ptr<Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc,
            const Viewport& viewport, const Color4& backColor)
            : mViewport(viewport), mBackColor(backColor), mEnableDepthStencil(true) {
            throwIfFailed(device->CreateRenderTargetView(texture->getTexture().Get(), desc, &mRenderTargetView));
            throwIfFailed(device->CreateDepthStencilView(depthStencilTexture->getTexture().Get(), dsvDesc, &mDepthStencilView));
        }

        RenderTargetView::~RenderTargetView() { }

        void RenderTargetView::clear(ID3D11DeviceContext* context) {
            context->ClearRenderTargetView(mRenderTargetView.Get(), mBackColor.get().data());
            if (mDepthStencilView && mEnableDepthStencil) {
                context->ClearDepthStencilView(mDepthStencilView.Get(),
                    D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);
            }
        }

        void RenderTargetView::set(ID3D11DeviceContext* context) {
            mViewport.set(context);
            if (mDepthStencilView && mEnableDepthStencil) {
                context->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
            }
            else {
                context->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
            }
        }

        void RenderTargetView::end(ID3D11DeviceContext* context) {
            ID3D11RenderTargetView* const view[] = { nullptr };
            context->OMSetRenderTargets(ARRAYSIZE(view), view, nullptr);
        }

        ComPtr<ID3D11RenderTargetView> RenderTargetView::getRenderTargetView() const {
            return mRenderTargetView;
        }

    } //Graphics 
} //Framework 
