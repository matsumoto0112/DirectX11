#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @struct ComputeShaderData
* @brief コンピュートシェーダの設定に必要なデータ群
*/
struct ComputeShaderData {
    Microsoft::WRL::ComPtr<ID3D11ComputeShader> mComputeShader; //!< ピクセルシェーダ
};

} //Graphics 
} //Framework 
