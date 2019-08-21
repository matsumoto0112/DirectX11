#include "VertexShaderResourceStorage.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {

namespace Utility {

VertexShaderResourceStorage::VertexShaderResourceStorage() {}

VertexShaderResourceStorage::~VertexShaderResourceStorage() {}

void VertexShaderResourceStorage::importResource(Define::VertexShaderType type, const std::string& filepath) {
    if (exist(type))return;
    mResources[type] = std::make_shared<Graphics::VertexShader>(filepath);
}

} //Utility 
} //Framework 

