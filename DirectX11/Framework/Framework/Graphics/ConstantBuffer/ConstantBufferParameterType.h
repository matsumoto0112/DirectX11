#pragma once
namespace Framework {
namespace Graphics {

/**
* @class ConstantBufferParameterType
* @brief �R���X�^���g�o�b�t�@�̈����v���p�e�B�̎��
*/
enum class ConstantBufferParameterType {
    World3D, //!< ���[���h�s��
    View3D, //!< �r���[�s��
    Projection3D, //!< �v���W�F�N�V�����s�� 
    World2D, //!< ���[���h�s��
    View2D, //!< �r���[�s��
    Projection2D, //!< �v���W�F�N�V�����s��
    UVLeft,
    UVTop,
    UVWidth,
    UVHeight,
    Color, //!< �F
    LightView, //!< ���C�g�r���[�s��
    LightProj, //!< ���C�g�v���W�F�N�V�����s��
};

} //Graphics 
} //Framework