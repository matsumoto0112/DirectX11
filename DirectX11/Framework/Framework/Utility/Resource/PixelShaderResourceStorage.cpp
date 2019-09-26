#include "PixelShaderResourceStorage.h"
#include "Framework/Utility/Resource/LoadResourceList.h"

namespace Framework {
namespace Utility {

PixelShaderResourceStorage::PixelShaderResourceStorage() {}

PixelShaderResourceStorage::~PixelShaderResourceStorage() {}

void PixelShaderResourceStorage::importResource(Define::PixelShaderType type) {
    if (isExist(type))return;
    mResources.emplace(type, std::make_shared<Graphics::PixelShader>(LoadResourceList::getPixelShaderPath(type)));
}

} //Utility 
} //Framework 
