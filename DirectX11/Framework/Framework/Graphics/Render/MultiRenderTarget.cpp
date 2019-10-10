#include "MultiRenderTarget.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Graphics/Shader/ShaderResourceView.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Math/Rect.h"

namespace {
using UINTPair = std::pair<UINT, UINT>;
UINTPair getTextureSize(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) {
    ID3D11Texture2D* texture;
    rtv->GetResource((ID3D11Resource**)&texture);
    D3D11_TEXTURE2D_DESC texDesc;
    texture->GetDesc(&texDesc);
    UINTPair res(texDesc.Width, texDesc.Height);
    texture->Release();
    return res;
}
}

namespace Framework {
namespace Graphics {

MultiRenderTarget::MultiRenderTarget(UINT renderTargetNum,
    std::vector<Texture2DPtr> texture,
    const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc,
    const Math::Rect& rect)
    :mRTVs(renderTargetNum),
    mDepthStencilView(nullptr),
    mViewport(std::make_unique<MultiViewport>(renderTargetNum, rect)),
    mRenderTargetTextures(renderTargetNum),
    mClearColor(Color4::WHITE),
    mUseDepthStencil(false) {
    for (UINT i = 0; i < renderTargetNum; i++) {
        DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture[i]->getBuffer().Get(), &rtvDesc, &mRTVs[i]);
        std::shared_ptr<ShaderResourceView> srv = std::make_shared<ShaderResourceView>(*texture[i], nullptr);
        mRenderTargetTextures[i] = std::make_shared<Texture>(
            texture[i],
            srv);
    }
}

MultiRenderTarget::MultiRenderTarget(UINT renderTargetNum, const Math::Rect& rect)
    :mRTVs(renderTargetNum),
    mDepthStencilView(nullptr),
    mViewport(std::make_unique<MultiViewport>(renderTargetNum, rect)),
    mRenderTargetTextures(renderTargetNum),
    mClearColor(Color4::WHITE),
    mUseDepthStencil(false) {
    D3D11_RENDER_TARGET_VIEW_DESC desc = RenderTargetViewDesc::getDefaultRenderTargetViewDesc();
    for (UINT i = 0; i < renderTargetNum; i++) {
        rect.getWidth();
        std::shared_ptr<TextureBuffer> texBuffer = std::make_shared<TextureBuffer>(
            RenderTargetViewDesc::getDefaultTexture2DDesc(
                static_cast<UINT>(rect.getWidth()),
                static_cast<UINT>(rect.getHeight())));
        DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texBuffer->getBuffer().Get(),
            &desc,
            &mRTVs[i]);
        std::shared_ptr<ShaderResourceView> srv = std::make_shared<ShaderResourceView>(*texBuffer, nullptr);
        mRenderTargetTextures[i] = std::make_shared<Texture>(texBuffer, srv);
    }
}

MultiRenderTarget::~MultiRenderTarget() {
    mRTVs.clear();
}

void MultiRenderTarget::createDepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc) {
    mDepthStencilView = std::make_unique<DepthStencilView>(texDesc, dsvDesc);
    mUseDepthStencil = true;
}

void MultiRenderTarget::createDepthStencilView() {
    const UINTPair size = getTextureSize(mRTVs[0]);
    mDepthStencilView = std::make_unique<DepthStencilView>(
        size.first,
        size.second);
    mUseDepthStencil = true;
}

void MultiRenderTarget::set() {
    if (mUseDepthStencil) {
        MY_ASSERTION(mDepthStencilView != nullptr, "深度・ステンシルビューが未作成です");
        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(mRTVs.size(),
            mRTVs[0].GetAddressOf(),
            mDepthStencilView->getDepthStencilView().Get());
    }
    else {
        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(mRTVs.size(),
            mRTVs[0].GetAddressOf(),
            nullptr);
    }
    mViewport->set();
}

void MultiRenderTarget::clear() {
    const UINT size = mRTVs.size();
    for (UINT i = 0; i < size; i++) {
        DX11InterfaceAccessor::getContext()->ClearRenderTargetView(mRTVs[i].Get(), mClearColor.get().data());
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
