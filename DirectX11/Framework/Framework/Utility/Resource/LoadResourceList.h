#pragma once
#include <unordered_map>
#include "Framework/Define/Resource/Model.h"
#include "Framework/Define/Resource/PixelShader.h"
#include "Framework/Define/Resource/Texture.h"
#include "Framework/Define/Resource/VertexShader.h"

namespace Framework {
namespace Utility {

/**
* @class LoadResourceList
* @brief �ǂݍ��ރ��\�[�X���X�g
*/
class LoadResourceList {
private:
    static const std::unordered_map<Define::ModelType, std::string> MODEL_LIST; //!< ���f�����X�g
    static const std::unordered_map<Define::PixelShaderType, std::string> PIXEL_SHADER_LIST; //!< �s�N�Z���V�F�[�_�[�̃��X�g
    static const std::unordered_map<Define::TextureType, std::string> TEXTURE_LIST; //!< �e�N�X�`�����X�g
    static const std::unordered_map<Define::VertexShaderType, std::string> VERTEX_SHADER_LIST; //!< ���_�V�F�[�_�[���X�g
public:
    static const std::string getModelPath(Define::ModelType type);
    static const std::string getPixelShaderPath(Define::PixelShaderType type);
    static const std::string getTexturePath(Define::TextureType type);
    static const std::string getVertexShaderPath(Define::VertexShaderType type);
};
} //Utility 
} //Framework 
