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
    Model_NoTexture,
    Model_Lighting,
    Model_Diffuse,
    Model_Diffuse_Lighting,
    Output_Z,
    Model_Shadow,
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
    static const std::string MODEL_DIFFUSE; //!< ディフューズテクスチャありモデル
    static const std::string MODEL_LIGHTING; //!< ライティングありモデル
    static const std::string MODEL_DIFFUSE_LIGHTING; //!< ディフューズテクスチャありライティングありモデル
    static const std::string OUTPUT_Z; //!< Z値を出力
    static const std::string MODEL_SHADOW; //!< Z値を出力
};

} //Define 