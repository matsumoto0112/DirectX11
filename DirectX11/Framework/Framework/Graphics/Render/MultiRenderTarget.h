#pragma once
#include <memory>
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class DepthStencilView;
class TextureBuffer;

/**
* @class MultiRenderTarget
* @brief マルチレンダーターゲット
*/
class MultiRenderTarget {
private:
    using Texture2DPtr = std::shared_ptr<TextureBuffer>;
    using RenderTargetViewPtr = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>;
public:
    /**
    * @brief コンストラクタ
    */
    MultiRenderTarget(UINT renderTargetNum, std::vector<Texture2DPtr> texture, const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc);
    /**
    * @brief デストラクタ
    */
    ~MultiRenderTarget();
    /**
    * @brief 深度・ステンシルビューを追加する
    */
    void bindDepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);
    /**
    * @brief レンダーターゲットをコンテキストにセットする
    */
    void set();
    /**
    * @brief レンダーターゲットをクリアする
    */
    void clear();
private:
    UINT mRenderTargetViewNum; //!< レンダーターゲットビューの数
    std::vector<RenderTargetViewPtr> mRTVs; //<! レンダーターゲットビュー配列
    std::unique_ptr<DepthStencilView> mDepthStencilView; //!< 深度・ステンシルビュー
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mUseDepthStencil, UseDepthStencil);
};

} //Graphics 
} //Framework 