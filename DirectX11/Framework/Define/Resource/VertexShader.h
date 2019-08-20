#pragma once
#include <string>
namespace Define {

/**
* @enum VertexShaderType
* @brief ���_�V�F�[�_��ޒ�`
*/
enum class VertexShaderType {
    Default2D,
    OnlyPosition,
    Default3D,
    Model,
    Lighting,

    Position3D,
};

/**
* @class VertexShader
* @brief ���_�V�F�[�_�[�̖��O�Ɋւ����`
*/
class VertexShaderName {
public:
    static const std::string DEFAULT_2D; //!< 2D�f�t�H���g���_�V�F�[�_�[
    static const std::string ONLY_POSITION; //!< ���_���݂̂̃V�F�[�_�[
    static const std::string DEFAULT_3D; //!< 3D�f�t�H���g���_�V�F�[�_�[
    static const std::string MODEL_NOLIGHTING; //!< ���C�e�B���O�Ȃ����f���p���_�V�F�[�_
    static const std::string MODEL_LIGHTING; //!< ���C�e�B���O���胂�f���p���_�V�F�[�_�[

    static const std::string POSITION3D;
};

} //Define 