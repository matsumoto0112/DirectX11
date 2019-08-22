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
    */
    DepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);
    /**
    * @brief デストラクタ
    */
    ~DepthStencilView();
    void clear();
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> getDepthStencilView() const { return mDepthStencil; }
private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencil;
};

} //Graphics 
} //Framework 