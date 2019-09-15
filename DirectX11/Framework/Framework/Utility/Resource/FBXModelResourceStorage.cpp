#include "FBXModelResourceStorage.h"
#include "Framework/Graphics/Model/FBXLoader.h"

namespace Framework {
namespace Utility {

Utility::FBXModelResourceStorage::FBXModelResourceStorage()
    :mFBXLoader(std::make_unique<Graphics::FBXLoader>()) {}

Utility::FBXModelResourceStorage::~FBXModelResourceStorage() {}

void Utility::FBXModelResourceStorage::importResource(Define::ModelType type, const std::string& filepath) {
    if (isExist(type))return;
    mResources.emplace(type, mFBXLoader->load(filepath));

}

} //Utility 
} //Framework 