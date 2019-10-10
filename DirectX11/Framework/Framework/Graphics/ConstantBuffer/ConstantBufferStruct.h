#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {

/**
* @brief 3DMVP行列
*/
struct MVPMatrix3DCBuffer {
    Math::Matrix4x4 world;
    Math::Matrix4x4 view;
    Math::Matrix4x4 proj;
};

/**
* @brief 2DMVP行列
*/
struct MVPMatrix2DCBuffer {
    Math::Matrix4x4 world;
    Math::Matrix4x4 view;
    Math::Matrix4x4 proj;
};

/**
* @brief UV情報
*/
struct UVInfoCBuffer {
    float left;
    float top;
    float width;
    float height;
};

/**
* @brief 色情報
*/
struct ColorCBuffer {
    Color4 color;
};

/**
* @brief ライト行列
*/
struct LightMatrixCBuffer {
    Math::Matrix4x4 lightView;
    Math::Matrix4x4 lightProj;
};

} //Graphics 
} //Framework 