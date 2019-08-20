#pragma once

#include "Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {

/**
* @struct MVPMatrixCBufferStruct
* @brief ���[���h�E�r���[�E�v���W�F�N�V�����s��
*/
struct MVPMatrixCBufferStruct {
public:
    Math::Matrix4x4 world; //!< ���[���h�s��
    Math::Matrix4x4 view; //!< �r���[�s��
    Math::Matrix4x4 proj; //!< �v���W�F�N�V�����s��
};

} //Graphics 
} //Framework