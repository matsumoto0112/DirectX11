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
* @brief 読み込むリソースリスト
*/
class LoadResourceList {
private:
    static const std::unordered_map<Define::ModelType, std::string> MODEL_LIST; //!< モデルリスト
    static const std::unordered_map<Define::PixelShaderType, std::string> PIXEL_SHADER_LIST; //!< ピクセルシェーダーのリスト
    static const std::unordered_map<Define::TextureType, std::string> TEXTURE_LIST; //!< テクスチャリスト
    static const std::unordered_map<Define::VertexShaderType, std::string> VERTEX_SHADER_LIST; //!< 頂点シェーダーリスト
public:
    static const std::string getModelPath(Define::ModelType type);
    static const std::string getPixelShaderPath(Define::PixelShaderType type);
    static const std::string getTexturePath(Define::TextureType type);
    static const std::string getVertexShaderPath(Define::VertexShaderType type);
};
} //Utility 
} //Framework 
