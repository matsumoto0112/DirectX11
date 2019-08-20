#pragma once

#include "Graphics/Color4.h"

namespace Framework {
namespace Graphics {

/**
* @struct PointLightCBufferStruct
* @brief ポイントライトのコンスタントバッファ構造体
*/
struct PointLightCBufferStruct {
public:
    Color4 color; //!< 色
    Math::Vector3 light; //!< ライトの座標
private:
    float dummy0; //!< パッキング対策
public:
    float attenuation[4]; //!< 減衰パラメータ
};

} //Graphics 
} //Framework