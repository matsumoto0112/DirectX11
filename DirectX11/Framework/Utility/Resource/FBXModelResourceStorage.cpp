#include "FBXModelResourceStorage.h"
#include "Graphics/Model/FBXLoader.h"
#include "Device/GameDevice.h"

namespace Framework {

namespace Utility {

Utility::FBXModelResourceStorage::FBXModelResourceStorage()
    :mFBXLoader(std::make_unique<Graphics::FBXLoader>()) {}

Utility::FBXModelResourceStorage::~FBXModelResourceStorage() {}

void Utility::FBXModelResourceStorage::importResource(Define::ModelType type, const std::string& filepath) {
    if (exist(type))return;
    mResources.emplace(type, mFBXLoader->load(filepath));

}

} //Utility 
} //Framework 