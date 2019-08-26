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
    Model_NoTexture,
    Model_Lighting,
    Model_Diffuse,
    Model_Diffuse_Lighting,
    Output_Z,
    Model_Shadow,
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
    static const std::string MODEL_DIFFUSE; //!< �f�B�t���[�Y�e�N�X�`�����胂�f��
    static const std::string MODEL_LIGHTING; //!< ���C�e�B���O���胂�f��
    static const std::string MODEL_DIFFUSE_LIGHTING; //!< �f�B�t���[�Y�e�N�X�`�����胉�C�e�B���O���胂�f��
    static const std::string OUTPUT_Z; //!< Z�l���o��
    static const std::string MODEL_SHADOW; //!< Z�l���o��
};

} //Define 