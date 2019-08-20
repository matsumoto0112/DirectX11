#pragma once

#include "Graphics/Color4.h"

namespace Framework {
namespace Graphics {

/**
* @struct PointLightCBufferStruct
* @brief �|�C���g���C�g�̃R���X�^���g�o�b�t�@�\����
*/
struct PointLightCBufferStruct {
public:
    Color4 color; //!< �F
    Math::Vector3 light; //!< ���C�g�̍��W
private:
    float dummy0; //!< �p�b�L���O�΍�
public:
    float attenuation[4]; //!< �����p�����[�^
};

} //Graphics 
} //Framework