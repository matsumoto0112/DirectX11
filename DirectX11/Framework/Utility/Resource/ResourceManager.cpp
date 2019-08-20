#include "ResourceManager.h"

namespace Framework {
namespace Utility {
ResourceManager::~ResourceManager() {
    mVertexShaders->clear();
    mPixelShaders->clear();
}

ResourceManager::ResourceManager()
    :mVertexShaders(std::make_unique<VertexShaderResourceStorage>()),
    mPixelShaders(std::make_unique<PixelShaderResourceStorage>()),
    mFBXModel(std::make_unique<FBXModelResourceStorage>()) {}

} //Utility 
} //Framework 
