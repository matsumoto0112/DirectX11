#pragma once

#include "Framework/Graphics/Color4.h"
#include "Framework/Math/Vector3.h"

namespace Framework {
namespace Graphics {

/**
* @struct DirectionalLightCBufferStruct
* @brief ディレクショナルライトのコンスタントバッファ用構造体
*/
struct DirectionalLightCBufferStruct {
public:
    Color4 color; //!< 色
    Math::Vector3 direction; //!< ライトの向き
private:
    float dummy; //!< パッキング対策
};


} //Graphics 
} //Framework
