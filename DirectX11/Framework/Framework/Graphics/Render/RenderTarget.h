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
class ShaderResourceView;
class TextureBuffer;

/**
* @class RenderTarget
* @brief レンダーターゲット
*/
class RenderTarget {
private:
    using DepthStencilViewPtr = std::unique_ptr<DepthStencilView>;
    using RenderTargetViewPtr = std::unique_ptr<RenderTargetView>;
    using ShaderResourceViewPtr = std::unique_ptr<ShaderResourceView>;
    using TexturePtr = std::shared_ptr<TextureBuffer>;
    using ViewportPtr = std::unique_ptr<Viewport>;
public:
    /**
    * @brief コンストラクタ
    * @param texture レンダーターゲットに使用するテクスチャ
    * @param viewport ビューポート
    * @param useSRV シェーダーリソースビューを使用するか
    */
    RenderTarget(TexturePtr texture, ViewportPtr viewport, SRVFlag useSRV);
    /**
    * @brief コンストラクタ
    * @param texture レンダーターゲットに使用するテクスチャ
    * @param rtvDesc レンダーターゲットのデスク
    * @param viewport ビューポート
    * @param useSRV シェーダーリソースビューを使用するか
    */
    RenderTarget(TexturePtr texture, const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc, ViewportPtr viewport, SRVFlag useSRV);
    /**
    * @brief デストラクタ
    */
    ~RenderTarget();
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
    RenderTargetViewPtr mRenderTargetView; //!< レンダーターゲット
    DepthStencilViewPtr mDepthStencilView; //!< 深度・ステンシルビュー
    ViewportPtr mViewport; //!< ビューポート
    ShaderResourceViewPtr mShaderResourceView; //!< レンダーターゲットのシェーダーリソースビュー
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mEnableDepthStencil, EnableDepthStencil);
};

} //Graphics 
} //Framework 