#pragma once
#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @class DepthStencilView
* @brief 深度・ステンシルビュー
*/
class DepthStencilView {
public:
    /**
    * @brief コンストラクタ
    * @param texDesc テクスチャデスク
    * @param dsvDesc 深度・ステンシルデスク
    */
    DepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);
    /**
    * @brief コンストラクタ
    * @param width 幅
    * @param height 高さ
    */
    DepthStencilView(UINT width, UINT height);
    /**
    * @brief デストラクタ
    */
    ~DepthStencilView();
    /**
    * @brief クリア
    */
    void clear();
    /**
    * @brief 深度・ステンシルビューの取得
    */
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> getDepthStencilView() const { return mDepthStencil; }
private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture; //!< テクスチャ 
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencil; //!< 深度・ステンシルビュー
};

} //Graphics 
} //Framework 