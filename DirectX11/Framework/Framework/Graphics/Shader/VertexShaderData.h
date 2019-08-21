#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @struct VertexShaderData
* @brief 頂点シェーダーの設定に必要なデータ群
*/
struct VertexShaderData {
    Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader; //!< 頂点シェーダ
    Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout; //!< インプットレイアウト
};

} //Graphics 
} //Framework 
