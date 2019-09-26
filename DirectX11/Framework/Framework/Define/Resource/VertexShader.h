#pragma once
namespace Define {

/**
* @enum VertexShaderType
* @brief 頂点シェーダ種類定義
*/
enum class VertexShaderType {
    NoAction,
    Texture2D,
    Model,
    Model_Lighting,
    Output_Z,
    Model_Shadow,
    Only_Position,
    Model_Shadow_Diffuse,
    Blackhole,
    Fall_Bounce_Rotate,
    Fall_Bounce,
    Fall,
    Firework,
    Flash,
    SpotInstancer,
    Wormhole,
};

} //Define 