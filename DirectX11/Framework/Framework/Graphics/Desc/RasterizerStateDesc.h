#pragma once

namespace Framework {
namespace Graphics {

/**
* @enum FillMode
* @brief 塗りつぶしの設定
*/
enum class FillMode {
    Solid,
    WireFrame,
};

/**
* @enum CullMode
* @brief カリングの設定
*/
enum class CullMode {
    None,
    Back,
    Front,
};

/**
* @class RasterizerStateDesc
* @brief ラスタライザ設定
*/
class RasterizerStateDesc {
public:
    /**
    * @brief DX11用FillModeに変換する
    */
    static const D3D11_FILL_MODE toD3D11_FILL_MODE(FillMode fill) {
        switch (fill) {
        case Framework::Graphics::FillMode::Solid:
            return D3D11_FILL_MODE::D3D11_FILL_SOLID;
        default:
            return D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
        }
    }
    /**
    * @brief DX11用CullModeに変換する
    */
    static const D3D11_CULL_MODE toD3D11_CULL_MODE(CullMode cull) {
        switch (cull) {
        case Framework::Graphics::CullMode::Back:
            return D3D11_CULL_MODE::D3D11_CULL_BACK;
        case Framework::Graphics::CullMode::Front:
            return D3D11_CULL_MODE::D3D11_CULL_FRONT;
        default:
            return D3D11_CULL_MODE::D3D11_CULL_NONE;
        }
    }

    /**
    * @brief デフォルト設定のラスタライザを取得する
    */
    static const D3D11_RASTERIZER_DESC getDefaultDesc(FillMode fill, CullMode cull) {
        D3D11_RASTERIZER_DESC desc{};
        desc.FillMode = toD3D11_FILL_MODE(fill);
        desc.CullMode = toD3D11_CULL_MODE(cull);
        desc.DepthClipEnable = TRUE;
        desc.MultisampleEnable = FALSE;
        desc.DepthBiasClamp = 0;
        desc.SlopeScaledDepthBias = 0;
        return desc;
    }
};

} //Graphics 
} //Framework 