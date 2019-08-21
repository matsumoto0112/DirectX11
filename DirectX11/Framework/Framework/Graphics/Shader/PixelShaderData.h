#pragma once

#include <d3d11.h>
#include <wrl/client.h>
namespace Framework {
namespace Graphics {

/**
* @struct PixelShaderData
* @brief ピクセルシェーダの設定に必要なデータ群
*/
struct PixelShaderData {
    Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader; //!< ピクセルシェーダ
};

} //Graphics 
} //Framework 
