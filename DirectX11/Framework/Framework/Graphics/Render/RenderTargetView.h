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
    */
    RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Color4& backColor);
    /**
    * @brief デストラクタ
    */
    ~RenderTargetView();
    /**
    * @brief レンダーターゲットビューを取得する
    */
    ComPtr<ID3D11RenderTargetView> getRenderTargetView() const { return mRenderTargetView; }
    /**
    * @brief レンダーターゲットのクリア
    */
    void clear();
    /**
    * @brief レンダーターゲットをセットする
    */
    void set();
private:
    ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< レンダーターゲットビュー
private:
    PROPERTY(Color4, mBackColor, BackColor);
};

} //Graphics 
} //Framework 
