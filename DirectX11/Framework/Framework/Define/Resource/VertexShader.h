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
};

} //Define 