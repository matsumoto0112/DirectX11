#pragma once

#include <wrl/client.h>
#include <d3d11.h>

namespace Framework {
namespace Graphics {

/**
* @struct VertexBufferBindData
* @brief 頂点バッファのバインドに必要なデータ群
*/
struct VertexBufferBindData {
    Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer; //!< バッファ
    UINT mStride; //!< 1頂点のサイズ
    UINT mOffset; //!< 頂点配列のオフセット値
};

} //Graphics 
} //Framework 