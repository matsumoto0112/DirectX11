#pragma once

#include "Framework/Math/Vector3.h"
#include "Framework/Graphics/Color4.h"

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
public:
    float R; //!< 最大到達距離
    float A; //!< 減衰率（0.0～2.0ぐらい）
private:
    float dummy[3]; //!< パッキング対策
};

} //Graphics 
} //Framework