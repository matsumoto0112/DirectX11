#pragma once
#include "Define/Render/Animation.h"
#include "Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {

/**
* @brief �{�[���s��\����
*/
struct BoneMatrixCBufferStruct {
    Math::Matrix4x4 bone[Define::Animation::BONE_MAX];
};

} //Graphics 
} //Framework