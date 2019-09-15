#include "PixelShaderResourceStorage.h"

namespace Framework {
namespace Utility {

PixelShaderResourceStorage::PixelShaderResourceStorage() {}

PixelShaderResourceStorage::~PixelShaderResourceStorage() {}

void PixelShaderResourceStorage::importResource(Define::PixelShaderType type, const std::string& filepath) {
    if (isExist(type))return;
    mResources.emplace(type, std::make_shared<Graphics::PixelShader>(filepath));
}

} //Utility 
} //Framework 
