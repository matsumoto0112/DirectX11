#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {

/**
* @brief 3DMVP�s��
*/
struct MVPMatrix3DCBuffer {
    Math::Matrix4x4 world;
    Math::Matrix4x4 view;
    Math::Matrix4x4 proj;
};

/**
* @brief 2DMVP�s��
*/
struct MVPMatrix2DCBuffer {
    Math::Matrix4x4 world;
    Math::Matrix4x4 view;
    Math::Matrix4x4 proj;
};

/**
* @brief UV���
*/
struct UVInfoCBuffer {
    float left;
    float top;
    float width;
    float height;
};

/**
* @brief �F���
*/
struct ColorCBuffer {
    Color4 color;
};

/**
* @brief ���C�g�s��
*/
struct LightMatrixCBuffer {
    Math::Matrix4x4 lightView;
    Math::Matrix4x4 lightProj;
};

} //Graphics 
} //Framework 