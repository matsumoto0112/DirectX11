#include "ResourceManager.h"

namespace Framework {
namespace Utility {
ResourceManager::~ResourceManager() {
    mVertexShaders->clear();
    mGeometoryShaders->clear();
    mPixelShaders->clear();
    mFBXModel->clear();
    mTexture->clear();
}

ResourceManager::ResourceManager()
    :mVertexShaders(std::make_unique<VertexShaderResourceStorage>()),
    mGeometoryShaders(std::make_unique<GeometoryShaderResourceStorage>()),
    mPixelShaders(std::make_unique<PixelShaderResourceStorage>()),
    mFBXModel(std::make_unique<FBXModelResourceStorage>()),
    mTexture(std::make_unique<TextureResourceStorage>()) { }

} //Utility 
} //Framework 
