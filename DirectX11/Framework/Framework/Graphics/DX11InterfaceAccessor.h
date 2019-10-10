#pragma once
#include <d3d11.h>
#include "Framework/Utility/TypeDef.h"

namespace Framework {
namespace Graphics {

/**
* @class DX11InterfaceAccessor
* @brief DirectX11インターフェースアクセサ
*/
class DX11InterfaceAccessor {
public:
    /**
    * @brief デバイスの取得
    */
    static ComPtr<ID3D11Device> getDevice();
    /**
    * @brief コンテキストの取得
    */
    static ComPtr<ID3D11DeviceContext> getContext();
};

} //Graphics 
} //Framework 