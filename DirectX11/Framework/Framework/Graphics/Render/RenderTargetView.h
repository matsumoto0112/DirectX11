#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Graphics/Color4.h"

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
    * @param resource リソーステクスチャ
    */
    RenderTargetView(Microsoft::WRL::ComPtr<ID3D11Resource> resource);
    /**
    * @brief コンストラクタ
    * @param resource リソーステクスチャ
    * @param desc レンダーターゲットビューの設定
    */
    RenderTargetView(Microsoft::WRL::ComPtr<ID3D11Resource> resource, const D3D11_RENDER_TARGET_VIEW_DESC& desc);
    /**
    * @brief デストラクタ
    */
    ~RenderTargetView();
    /**
    * @brief レンダーターゲットを設定する
    */
    void set();
    /**
    * @brief レンダーターゲットビューのクリア処理
    */
    void clear(const Color4& clearColor);
    /**
    * @brief 深度・ステンシルビューをバインドする
    */
    void bindDepthStencilView(std::unique_ptr<DepthStencilView> depthStencil) { mDepthStencil = std::move(depthStencil); }
private:
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< レンダーターゲットビュー
    std::unique_ptr<DepthStencilView> mDepthStencil; //!< 深度・ステンシルビュー
};

} //Graphics 
} //Framework 
