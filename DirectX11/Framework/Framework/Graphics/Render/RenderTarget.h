#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Render/SRVFlag.h"
#include "Framework/Graphics/Render/Viewport.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class DepthStencilView;
class RenderTargetView;
class Texture;
class TextureBuffer;

/**
* @class RenderTarget
* @brief レンダーターゲット
*/
class RenderTarget {
private:
    using DepthStencilViewPtr = std::unique_ptr<DepthStencilView>;
    using RenderTargetViewPtr = std::unique_ptr<RenderTargetView>;
    using TexturePtr = std::shared_ptr<Texture>;
    using TextureBufferPtr = std::shared_ptr<TextureBuffer>;
    using ViewportPtr = std::unique_ptr<Viewport>;
public:
    /**
    * @brief コンストラクタ
    * @param texture レンダーターゲットに使用するテクスチャ
    * @param viewport ビューポート
    * @param useSRV シェーダーリソースビューを使用するか
    */
    RenderTarget(TextureBufferPtr texture, ViewportPtr viewport, SRVFlag useSRV);
    /**
    * @brief コンストラクタ
    * @param texture レンダーターゲットに使用するテクスチャ
    * @param rtvDesc レンダーターゲットのデスク
    * @param viewport ビューポート
    * @param useSRV シェーダーリソースビューを使用するか
    */
    RenderTarget(TextureBufferPtr texture, const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc, ViewportPtr viewport, SRVFlag useSRV);
    /**
    * @brief デストラクタ
    */
    ~RenderTarget();
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
    */
    TexturePtr getRenderTargetTexture();
private:
    RenderTargetViewPtr mRenderTargetView; //!< レンダーターゲット
    DepthStencilViewPtr mDepthStencilView; //!< 深度・ステンシルビュー
    ViewportPtr mViewport; //!< ビューポート
    TexturePtr mTexture; //!< レンダーターゲットのテクスチャ
private:
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mEnableDepthStencil, EnableDepthStencil);
};

} //Graphics 
} //Framework 