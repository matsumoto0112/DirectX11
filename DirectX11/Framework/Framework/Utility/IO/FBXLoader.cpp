#include "FBXLoader.h"

namespace Framework {
namespace Utility {
FBXLoader::FBXLoader(const std::string& filepath) { }

FBXLoader::~FBXLoader() {
    mManager->Destroy();
}

} //Utility 
} //Framework 