#pragma once
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
    Model_Shadow_Diffuse,
};

} //Define 