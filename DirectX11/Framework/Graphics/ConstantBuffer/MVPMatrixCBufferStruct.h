#pragma once

#include "Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {

/**
* @struct MVPMatrixCBufferStruct
* @brief ワールド・ビュー・プロジェクション行列
*/
struct MVPMatrixCBufferStruct {
public:
    Math::Matrix4x4 world; //!< ワールド行列
    Math::Matrix4x4 view; //!< ビュー行列
    Math::Matrix4x4 proj; //!< プロジェクション行列
};

} //Graphics 
} //Framework