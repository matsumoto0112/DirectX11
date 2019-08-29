#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class TextureBuffer;
/**
* @class RenderTargetView
* @brief レンダーターゲットビュー
*/
class RenderTargetView {
private:
    using TexturePtr = std::shared_ptr<TextureBuffer>;
public:
    /**
    * @brief コンストラクタ
    * @param texture リソーステクスチャ
    */
    RenderTargetView(TexturePtr texture);
    /**
    * @brief コンストラクタ
    * @param texture リソーステクスチャ
    * @param desc レンダーターゲットビューの設定
    */
    RenderTargetView(TexturePtr texture, const D3D11_RENDER_TARGET_VIEW_DESC& desc);
    /**
    * @brief デストラクタ
    */
    ~RenderTargetView();
    /**
    * @brief レンダーターゲットビューを取得する
    */
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> getRenderTargetView() const { return mRenderTargetView; }
    /**
    * @brief レンダーターゲットのクリア
    * @param clearColor クリア色
    */
    void clear(const Color4& clearColor);
private:
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< レンダーターゲットビュー
};

} //Graphics 
} //Framework 
