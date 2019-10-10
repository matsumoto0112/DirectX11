#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Resource/Texture2D.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
/**
* @class RenderTargetView
* @brief レンダーターゲットビュー
*/
class RenderTargetView {
public:
    /**
    * @brief コンストラクタ
    * @param texture リソーステクスチャ
    * @param desc レンダーターゲットビューの設定
    * @param backColor 背景色
    */
    RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Color4& backColor);
    /**
    * @brief コンストラクタ
    * @param textures リソーステクスチャ配列
    * @param desc レンダーターゲットビューの設定
    * @param backColor 背景色
    */
    RenderTargetView(std::vector<std::shared_ptr<Texture2D>> textures, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Color4& backColor);
    /**
    * @brief コンストラクタ
    * @param texture リソーステクスチャ
    * @param desc レンダーターゲットビューの設定
    * @param depthStencilTexture 深度・ステンシルビューテクスチャ
    * @param dsvDesc 深度・ステンシルビューの設定
    * @param backColor 背景色
    */
    RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
        std::shared_ptr<Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc, const Color4& backColor);
    /**
    * @brief コンストラクタ
    * @param textures リソーステクスチャ配列
    * @param desc レンダーターゲットビューの設定
    * @param depthStencilTexture 深度・ステンシルビューテクスチャ
    * @param dsvDesc 深度・ステンシルビューの設定
    * @param backColor 背景色
    */
    RenderTargetView(std::vector<std::shared_ptr<Texture2D>> textures, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
        std::shared_ptr<Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc, const Color4& backColor);
    /**
    * @brief デストラクタ
    */
    ~RenderTargetView();
    /**
    * @brief レンダーターゲットビューを取得する
    */
    ComPtr<ID3D11RenderTargetView> getRenderTargetView(UINT n = 0) const;
    /**
    * @brief レンダーターゲットのクリア
    */
    void clear();
    /**
    * @brief レンダーターゲットをセットする
    */
    void set();
    /**
    * @brief 描画終了
    */
    void end();
private:
    std::vector<ComPtr<ID3D11RenderTargetView>> mRenderTargetView; //!< レンダーターゲットビュー
    ComPtr<ID3D11DepthStencilView> mDepthStencilView; //!< 深度・ステンシルビュー
private:
    PROPERTY(Color4, mBackColor, BackColor);
};

} //Graphics 
} //Framework 
