#include "GeometoryShaderResourceStorage.h"
#include "Framework/Utility/Resource/LoadResourceList.h"

namespace Framework {
namespace Utility {

GeometoryShaderResourceStorage::GeometoryShaderResourceStorage() {}

GeometoryShaderResourceStorage::~GeometoryShaderResourceStorage() {}

void GeometoryShaderResourceStorage::importResource(Define::GeometoryShader type) {
    if (isExist(type))return;
    mResources.emplace(type, std::make_shared<Graphics::GeometoryShader>(LoadResourceList::getGeometoryShaderPath(type)));
}

} //Utility 
} //Framework 
