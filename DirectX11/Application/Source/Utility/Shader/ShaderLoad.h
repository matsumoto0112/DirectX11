#pragma once
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Graphics/Shader/ComputeShader.h"

/**
* @class ShaderLoad
* @brief discription
*/
class ShaderLoad {
public:
    static std::shared_ptr<Framework::Graphics::VertexShader> loadVS(const std::string& filenameFromShaderFolder);
    static std::shared_ptr<Framework::Graphics::GeometoryShader> loadGS(const std::string& filenameFromShaderFolder);
    static std::shared_ptr<Framework::Graphics::PixelShader> loadPS(const std::string& filenameFromShaderFolder);
    static std::shared_ptr<Framework::Graphics::ComputeShader> loadCS(
        const std::string& filenameFromShaderFolder, const Framework::Graphics::ComputeShader::Info& info);
};