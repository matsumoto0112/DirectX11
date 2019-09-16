#pragma once

#include <d3d11.h>
#include <wrl/client.h>
namespace Framework {
namespace Graphics {

/**
* @struct GeometoryShaderData
* @brief ジオメトリシェーダの設定に必要なデータ群
*/
struct GeometoryShaderData {
    Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometoryShader; //!< ジオメトリシェーダ
};

} //Graphics 
} //Framework 
