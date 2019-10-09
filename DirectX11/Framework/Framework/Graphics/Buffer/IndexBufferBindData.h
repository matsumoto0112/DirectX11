#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include "Framework/Graphics/Renderer/PrimitiveTopology.h"

namespace Framework {
namespace Graphics {

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