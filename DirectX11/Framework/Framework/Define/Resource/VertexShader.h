#pragma once
#include <string>
namespace Define {

/**
* @enum VertexShaderType
* @brief 頂点シェーダ種類定義
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
* @brief 頂点シェーダーの名前に関する定義
*/
class VertexShaderName {
public:
    static const std::string TEXTURE2D; //!< 2Dデフォルト
    static const std::string MODEL; //!< 通常モデル
    static const std::string MODEL_LIGHTING; //!< ライティングありモデル
    static const std::string OUTPUT_Z; //!< Z値を出力
    static const std::string MODEL_SHADOW;
    static const std::string ONLY_POSITION; //!< 座標のみを出力する
};

} //Define 