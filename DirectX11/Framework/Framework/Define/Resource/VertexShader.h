#pragma once
#include <string>
namespace Define {

/**
* @enum VertexShaderType
* @brief ���_�V�F�[�_��ޒ�`
*/
enum class VertexShaderType {
    Texture2D,
    Model,
    Model_Lighting,
    Output_Z,
    Model_Shadow,
    Only_Position,
};

/**
* @class VertexShader
* @brief ���_�V�F�[�_�[�̖��O�Ɋւ����`
*/
class VertexShaderName {
public:
    static const std::string TEXTURE2D; //!< 2D�f�t�H���g
    static const std::string MODEL; //!< �ʏ탂�f��
    static const std::string MODEL_LIGHTING; //!< ���C�e�B���O���胂�f��
    static const std::string OUTPUT_Z; //!< Z�l���o��
    static const std::string MODEL_SHADOW;
    static const std::string ONLY_POSITION; //!< ���W�݂̂��o�͂���
};

} //Define 