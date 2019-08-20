#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Graphics/Color4.h"

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
    RenderTargetView(ID3D11Resource* resource);
    /**
    * @brief コンストラクタ
    * @param resource リソーステクスチャ
    * @param desc レンダーターゲットビューの設定
    */
    RenderTargetView(ID3D11Resource* resource, D3D11_RENDER_TARGET_VIEW_DESC* desc);
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
private:
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
};

} //Graphics 
} //Framework 
