#pragma once
#include <string>
namespace Define {

/**
* @enum PixelShaderType
* @brief �s�N�Z���V�F�[�_�̎�ޒ�`
*/
enum class PixelShaderType {
    Default2D,
    OnlyPosition,
    NoTextureNoLighting,
    NoTextureLighting,
    Model,
    ModelLighting,
    Blend,
    RedModel,
    Position3D,
};

/**
* @class PixelShaderName
* @brief �s�N�Z���V�F�[�_�[�̖��O�Ɋւ����`
*/
class PixelShaderName {
public:
    static const std::string DEFAULT_2D;  //!< 2D�s�N�Z���V�F�[�_�[
    static const std::string ONLY_POSITION; //!< ���_���݂̂̃V�F�[�_�[
    static const std::string MODEL_NOTEXTURE_NOLIGHTING;
    static const std::string MODEL_NOTEXTURE_LIGHTING;
    static const std::string MODEL_NOLIGHTING; //!< ���C�e�B���O�Ȃ����f���p�s�N�Z���V�F�[�_�[
    static const std::string MODEL_LIGHTING; //!< ���C�e�B���O���胂�f���p�s�N�Z���V�F�[�_�[
    static const std::string CAMERA_BLEND; //!< �J�����̃����_�����O���ʍ����p�s�N�Z���V�F�[�_�[
    static const std::string RED_MODEL; //!< ���f����Ԃ�����V�F�[�_�[

    static const std::string POSITION3D;
};

} //Define 