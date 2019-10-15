#include "ShaderLoad.h"
#include "Framework/Define/Path.h"

using namespace Framework::Define;
using namespace Framework::Graphics;

std::shared_ptr<VertexShader> ShaderLoad::loadVS(const std::string& filename) {
    const std::string shaderPath = Path::getInstance()->shader();
    return std::make_shared<VertexShader>(shaderPath + filename);
}

std::shared_ptr<GeometoryShader> ShaderLoad::loadGS(const std::string& filename) {
    const std::string shaderPath = Path::getInstance()->shader();
    return std::make_shared<GeometoryShader>(shaderPath + filename);
}

std::shared_ptr<PixelShader> ShaderLoad::loadPS(const std::string& filename) {
    const std::string shaderPath = Path::getInstance()->shader();
    return std::make_shared<PixelShader>(shaderPath + filename);
}

std::shared_ptr<ComputeShader> ShaderLoad::loadCS(const std::string& filename, const ComputeShader::Info& info) {
    const std::string shaderPath = Path::getInstance()->shader();
    return std::make_shared<ComputeShader>(shaderPath + filename, info);
}
