#pragma once
namespace Framework {
namespace Graphics {

/**
* @class ConstantBufferParameterType
* @brief コンスタントバッファの扱うプロパティの種類
*/
enum class ConstantBufferParameterType {
    World3D, //!< ワールド行列
    View3D, //!< ビュー行列
    Projection3D, //!< プロジェクション行列 
    World2D, //!< ワールド行列
    View2D, //!< ビュー行列
    Projection2D, //!< プロジェクション行列
    UVLeft,
    UVTop,
    UVWidth,
    UVHeight,
    Color, //!< 色
    LightView, //!< ライトビュー行列
    LightProj, //!< ライトプロジェクション行列
};

} //Graphics 
} //Framework