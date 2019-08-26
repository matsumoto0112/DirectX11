#pragma once
namespace Framework {
namespace Graphics {

/**
* @class ConstantBufferParameterType
* @brief �R���X�^���g�o�b�t�@�̈����v���p�e�B�̎��
*/
enum class ConstantBufferParameterType {
    World, //!< ���[���h�s��
    View, //!< �r���[�s��
    Projection, //!< �v���W�F�N�V�����s��
    UV, //!< UV
    Light, //!< ���C�e�B���O
    Color, //!< �F
    Time, //!< ����
    CameraNum, //!< �J�����̐�
    Ambient,
    Diffuse,
    Specular,
    Shininess,
    Alpha,

    LightMat,
};

} //Graphics 
} //Framework