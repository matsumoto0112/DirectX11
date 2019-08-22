#pragma once
#include <string>
namespace Define {

/**
* @enum PixelShaderType
* @brief ピクセルシェーダの種類定義
*/
enum class PixelShaderType {
    Texture2D,
    Model,
    Nodel_NoTexture,
    Model_Lighting,
};

/**
* @class PixelShaderName
* @brief ピクセルシェーダーの名前に関する定義
*/
class PixelShaderName {
public:
    static const std::string TEXTURE2D; //!< 2Dテクスチャ
    static const std::string MODEL; //!< 通常モデル
    static const std::string MODEL_NOTEXTURE; //!< テクスチャなしモデル
    static const std::string MODEL_LIGHTING; //!< ライティングありモデル
};

} //Define 