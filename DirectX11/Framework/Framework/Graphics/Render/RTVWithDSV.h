#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class RTVWithDSV
* @brief 深度・ステンシルビュー付きレンダーターゲット
*/
class RTVWithDSV {
public:
    /**
    * @brief コンストラクタ
    */
    RTVWithDSV(ComPtr<ID3D11Texture2D> renderTargetTexture, const D3D11_RENDER_TARGET_VIEW_DESC* rtvDesc,
        ComPtr<ID3D11Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc);
    /**
    * @brief デストラクタ
    */
    ~RTVWithDSV();
    /**
    * @brief レンダーターゲット・深度・ステンシルビューのクリア
    */
    void clear();
    /**
    * @brief レンダーターゲットのセット
    */
    void set();
private:
    ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< レンダーターゲットビュー
    ComPtr<ID3D11DepthStencilView> mDepthStencilView; //!< 深度・ステンシルビュー
private:
    PROPERTY(Color4, mBackColor, BackColor);
};

} //Graphics 
} //Framework 