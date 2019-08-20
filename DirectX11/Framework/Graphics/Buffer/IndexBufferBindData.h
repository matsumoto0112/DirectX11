#pragma once

#include <wrl/client.h>
#include <d3d11.h>

namespace Framework {
namespace Graphics {

/**
* @enum PrimitiveTopology
* @brief プリミティブトポロジーの種類
*/
enum class PrimitiveTopology {
    LineList, //!< ラインリスト
    TriangleList, //!< 三角形リスト
    TriangleStrip, //!< 三角形ストリップ
    NONE,
};

/**
* @struct IndexBufferBindData
* @brief インデックスバッファをデバイスにバインドするのに必要なデータ
*/
struct IndexBufferBindData {
    Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer; //!< インデックスバッファ
    D3D11_PRIMITIVE_TOPOLOGY mTopology; //!< プリミティブトポロジーの種類
};

} //Graphics 
} //Framework 