#include "VertexShaderResourceStorage.h"

namespace Framework {
namespace Utility {

VertexShaderResourceStorage::VertexShaderResourceStorage() {}

VertexShaderResourceStorage::~VertexShaderResourceStorage() {}

void VertexShaderResourceStorage::importResource(Define::VertexShaderType type, const std::string& filepath) {
    if (isExist(type))return;
    mResources.emplace(type, std::make_shared<Graphics::VertexShader>(filepath));
}

} //Utility 
} //Framework 

