#pragma once
#include <string>
namespace Define {

/**
* @enum PixelShaderType
* @brief ピクセルシェーダの種類定義
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
* @brief ピクセルシェーダーの名前に関する定義
*/
class PixelShaderName {
public:
    static const std::string DEFAULT_2D;  //!< 2Dピクセルシェーダー
    static const std::string ONLY_POSITION; //!< 頂点情報のみのシェーダー
    static const std::string MODEL_NOTEXTURE_NOLIGHTING;
    static const std::string MODEL_NOTEXTURE_LIGHTING;
    static const std::string MODEL_NOLIGHTING; //!< ライティングなしモデル用ピクセルシェーダー
    static const std::string MODEL_LIGHTING; //!< ライティングありモデル用ピクセルシェーダー
    static const std::string CAMERA_BLEND; //!< カメラのレンダリング結果合成用ピクセルシェーダー
    static const std::string RED_MODEL; //!< モデルを赤くするシェーダー

    static const std::string POSITION3D;
};

} //Define 