#include "MultiRenderTarget.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

MultiRenderTarget::MultiRenderTarget(UINT renderTargetNum,
    std::vector<Texture2DPtr> texture,
    const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc,
    const Math::Rect& rect)
    :mRTVs(renderTargetNum), mViewport(std::make_unique<MultiViewport>(renderTargetNum, rect)) {
    for (UINT i = 0; i < renderTargetNum; i++) {
        Utility::getDevice()->CreateRenderTargetView(texture[i]->getBuffer().Get(), &rtvDesc, &mRTVs[i]);
    }
}

MultiRenderTarget::~MultiRenderTarget() {
    mRTVs.clear();
}

void MultiRenderTarget::bindDepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc) {
    mDepthStencilView = std::make_unique<DepthStencilView>(texDesc, dsvDesc);
    mUseDepthStencil = true;
}

void MultiRenderTarget::set() {
    if (mUseDepthStencil) {
        MY_ASSERTION(mDepthStencilView != nullptr, "�[�x�E�X�e���V���r���[�����쐬�ł�");
        Utility::getContext()->OMSetRenderTargets(mRTVs.size(),
            mRTVs[0].GetAddressOf(),
            mDepthStencilView->getDepthStencilView().Get());
    }
    else {
        Utility::getContext()->OMSetRenderTargets(mRTVs.size(),
            mRTVs[0].GetAddressOf(),
            nullptr);
    }
    mViewport->set();
}

void MultiRenderTarget::clear() {
    const UINT size = mRTVs.size();
    for (UINT i = 0; i < size; i++) {
        Utility::getContext()->ClearRenderTargetView(mRTVs[i].Get(), mClearColor.get().data());
    }
    if (mUseDepthStencil && mDepthStencilView) {
        mDepthStencilView->clear();
    }
}

} //Graphics 
} //Framework 