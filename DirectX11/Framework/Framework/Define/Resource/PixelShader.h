#pragma once
#include <string>
namespace Define {

/**
* @enum PixelShaderType
* @brief �s�N�Z���V�F�[�_�̎�ޒ�`
*/
enum class PixelShaderType {
    Texture2D,
    Model,
    Nodel_NoTexture,
    Model_Lighting,
};

/**
* @class PixelShaderName
* @brief �s�N�Z���V�F�[�_�[�̖��O�Ɋւ����`
*/
class PixelShaderName {
public:
    static const std::string TEXTURE2D; //!< 2D�e�N�X�`��
    static const std::string MODEL; //!< �ʏ탂�f��
    static const std::string MODEL_NOTEXTURE; //!< �e�N�X�`���Ȃ����f��
    static const std::string MODEL_LIGHTING; //!< ���C�e�B���O���胂�f��
};

} //Define 