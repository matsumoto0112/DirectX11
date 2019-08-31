#pragma once
#include <d3d11.h>

namespace Framework {
namespace Graphics {

/**
* @class RenderTargetViewDesc
* @brief レンダーターゲットビューに使用するデスク
*/
class RenderTargetViewDesc {
public:
    static constexpr DXGI_FORMAT DefaultFormat = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; //<! デフォルトのフォーマット
    /**
    * @brief デフォルトのテクスチャ2Dデスクを取得する
    * @param width 幅
    * @param height 高さ
    */
    static constexpr D3D11_TEXTURE2D_DESC getDefaultTexture2DDesc(UINT width, UINT height) {
        D3D11_TEXTURE2D_DESC texDesc{};
        texDesc.Width = width;
        texDesc.Height = height;
        texDesc.MipLevels = 1;
        texDesc.ArraySize = 1;
        texDesc.Format = DefaultFormat;
        texDesc.SampleDesc.Count = 1;
        texDesc.SampleDesc.Quality = 0;
        texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
        texDesc.CPUAccessFlags = 0;
        return texDesc;
    }
    /**
    * @brief デフォルトのレンダーターゲットビューデスクを取得する
    */
    static constexpr D3D11_RENDER_TARGET_VIEW_DESC getDefaultRenderTargetViewDesc() {
        D3D11_RENDER_TARGET_VIEW_DESC viewDesc{};
        viewDesc.Format = DefaultFormat;
        viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        return viewDesc;
    }
};

} //Graphics 
} //Framework 