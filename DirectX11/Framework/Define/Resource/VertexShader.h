#pragma once
#include <string>
namespace Define {

/**
* @enum VertexShaderType
* @brief 頂点シェーダ種類定義
*/
enum class VertexShaderType {
    Default2D,
    OnlyPosition,
    Default3D,
    Model,
    Lighting,

    Position3D,
};

/**
* @class VertexShader
* @brief 頂点シェーダーの名前に関する定義
*/
class VertexShaderName {
public:
    static const std::string DEFAULT_2D; //!< 2Dデフォルト頂点シェーダー
    static const std::string ONLY_POSITION; //!< 頂点情報のみのシェーダー
    static const std::string DEFAULT_3D; //!< 3Dデフォルト頂点シェーダー
    static const std::string MODEL_NOLIGHTING; //!< ライティングなしモデル用頂点シェーダ
    static const std::string MODEL_LIGHTING; //!< ライティングありモデル用頂点シェーダー

    static const std::string POSITION3D;
};

} //Define 