#pragma once
#include <memory>
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Render/MultiViewport.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class DepthStencilView;
class TextureBuffer;
class Texture;

/**
* @class MultiRenderTarget
* @brief マルチレンダーターゲット
*/
class MultiRenderTarget {
private:
    using Texture2DPtr = std::shared_ptr<TextureBuffer>;
    using RenderTargetViewPtr = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>;
    using MultiViewportPtr = std::unique_ptr<MultiViewport>;
    using TexturePtr = std::shared_ptr<Texture>;
public:
    /**
    * @brief コンストラクタ
    * @param renderTargetNum レンダーターゲット数
    * @param textures 使用するテクスチャバッファ配列
    * @param rtvDesc レンダーターゲットデスク
    * @param rect レンダーターゲットの範囲
    */
    MultiRenderTarget(UINT renderTargetNum,
        std::vector<Texture2DPtr> textures,
        const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc,
        const Math::Rect& rect);
    /**
    * @brief コンストラクタ
    * @param renderTargetNum レンダーターゲット数
    * @param rect レンダーターゲットの範囲
    * @details デフォルトのレンダーターゲットの仕様で作成する
    */
    MultiRenderTarget(UINT renderTargetNum,
        const Math::Rect& rect);
    /**
    * @brief デストラクタ
    */
    ~MultiRenderTarget();
    /**
    * @brief 深度・ステンシルビューをデフォルトの仕様で作成する
    */
    void createDepthStencilView();
    /**
    * @brief 深度・ステンシルビューを作成する
    */
    void createDepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);
    /**
    * @brief レンダーターゲットをコンテキストにセットする
    */
    void set();
    /**
    * @brief レンダーターゲットをクリアする
    */
    void clear();
    /**
    * @brief レンダーターゲットのテクスチャを取得する
    * @param num 配列のインデックス
    */
    TexturePtr getRenderTargetTexture(UINT index);
private:
    std::vector<RenderTargetViewPtr> mRTVs; //<! レンダーターゲットビュー配列
    std::unique_ptr<DepthStencilView> mDepthStencilView; //!< 深度・ステンシルビュー
    MultiViewportPtr mViewport; //!< ビューポート
    std::vector<TexturePtr> mRenderTargetTextures; //!< レンダーターゲットのテクスチャ配列
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mUseDepthStencil, UseDepthStencil);
};

} //Graphics 
} //Framework 