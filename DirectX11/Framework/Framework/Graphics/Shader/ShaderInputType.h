#pragma once
namespace Framework {
namespace Graphics {

/**
* @enum ShaderInputType
* @brief シェーダに値を代入する際どのシェーダに代入するか
*/
enum class ShaderInputType {
    Vertex, //!< 頂点シェーダのみ
    Pixel, //!< ピクセルシェーダのみ
    Compute,
    Geometory,
    VertexAndPixel, //頂点・ピクセルシェーダ両方
    All,
};

} //Graphics 
} //Framework 
