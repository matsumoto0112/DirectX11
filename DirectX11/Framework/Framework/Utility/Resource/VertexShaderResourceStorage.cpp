#include "VertexShaderResourceStorage.h"
#include "Framework/Utility/Resource/LoadResourceList.h"

namespace Framework {
namespace Utility {

VertexShaderResourceStorage::VertexShaderResourceStorage() {}

VertexShaderResourceStorage::~VertexShaderResourceStorage() {}

void VertexShaderResourceStorage::importResource(Define::VertexShaderType type) {
    if (isExist(type))return;
    mResources.emplace(type, std::make_shared<Graphics::VertexShader>(LoadResourceList::getVertexShaderPath(type)));
}

} //Utility 
} //Framework 

