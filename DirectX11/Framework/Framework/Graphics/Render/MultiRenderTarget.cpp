#include "MultiRenderTarget.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Graphics/Shader/ShaderResourceView.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

MultiRenderTarget::MultiRenderTarget(UINT renderTargetNum,
    std::vector<Texture2DPtr> texture,
    const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc,
    const Math::Rect& rect)
    :mRTVs(renderTargetNum),
    mViewport(std::make_unique<MultiViewport>(renderTargetNum, rect)),
    mRenderTargetTextures(renderTargetNum) {
    for (UINT i = 0; i < renderTargetNum; i++) {
        Utility::getDevice()->CreateRenderTargetView(texture[i]->getBuffer().Get(), &rtvDesc, &mRTVs[i]);
        std::shared_ptr<ShaderResourceView> srv = std::make_shared<ShaderResourceView>(*texture[i], nullptr);
        mRenderTargetTextures[i] = std::make_shared<Texture>(
            texture[i],
            srv);
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
        MY_ASSERTION(mDepthStencilView != nullptr, "深度・ステンシルビューが未作成です");
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

MultiRenderTarget::TexturePtr MultiRenderTarget::getRenderTargetTexture(UINT index) {
    MY_ASSERTION(index < mRenderTargetTextures.size(), "配列の範囲外です");
    return mRenderTargetTextures[index];
}

} //Graphics 
} //Framework 
