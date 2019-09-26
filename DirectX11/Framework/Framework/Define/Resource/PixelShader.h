#pragma once
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
    Model_Diffuse_Split4Color,
    Output_Color,
    Texture2D_Inversion,
    Model_Shadow_Diffuse,
    Model_Shadow_Color,
};

} //Define 