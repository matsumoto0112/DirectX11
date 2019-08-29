#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class RenderTargetView;
class DepthStencilView;
class TextureBuffer;

/**
* @class RenderTarget
* @brief レンダーターゲット
*/
class RenderTarget {
private:
    using TexturePtr = std::shared_ptr<TextureBuffer>;
public:
    /**
    * @brief コンストラクタ
    * @param texture レンダーターゲットに使用するテクスチャ
    */
    RenderTarget(TexturePtr texture);
    /**
    * @brief コンストラクタ
    * @param texture レンダーターゲットに使用するテクスチャ
    * @param rtvDesc レンダーターゲットのデスク
    */
    RenderTarget(TexturePtr texture, const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc);
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
    std::unique_ptr<RenderTargetView> mRenderTargetView; //!< レンダーターゲット
    std::unique_ptr<DepthStencilView> mDepthStencilView; //!< 深度・ステンシルビュー
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mUseDepthStencil, UseDepthStencil);
};

} //Graphics 
} //Framework 