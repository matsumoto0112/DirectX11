#include "FBXModelResourceStorage.h"
#include "Framework/Graphics/Model/FBXLoader.h"
#include "Framework/Utility/Resource/LoadResourceList.h"

namespace Framework {
namespace Utility {

Utility::FBXModelResourceStorage::FBXModelResourceStorage()
    :mFBXLoader(std::make_unique<Graphics::FBXLoader>()) {}

Utility::FBXModelResourceStorage::~FBXModelResourceStorage() {}

void FBXModelResourceStorage::importResource(Define::ModelType type) {
    if (isExist(type))return;
    mResources.emplace(type, mFBXLoader->load(LoadResourceList::getModelPath(type)));
}

} //Utility 
} //Framework 