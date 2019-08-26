#pragma once
namespace Framework {
namespace Graphics {

/**
* @class ConstantBufferParameterType
* @brief コンスタントバッファの扱うプロパティの種類
*/
enum class ConstantBufferParameterType {
    World, //!< ワールド行列
    View, //!< ビュー行列
    Projection, //!< プロジェクション行列
    UV, //!< UV
    Light, //!< ライティング
    Color, //!< 色
    Time, //!< 時間
    CameraNum, //!< カメラの数
    Ambient,
    Diffuse,
    Specular,
    Shininess,
    Alpha,

    LightMat,
};

} //Graphics 
} //Framework