#pragma once

#include "Framework/Math/Vector3.h"
#include "Framework/Graphics/Color4.h"

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
public:
    float R; //!< �ő哞�B����
    float A; //!< �������i0.0�`2.0���炢�j
private:
    float dummy[3]; //!< �p�b�L���O�΍�
};

} //Graphics 
} //Framework