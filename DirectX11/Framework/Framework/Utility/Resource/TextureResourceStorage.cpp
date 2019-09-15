#include "TextureResourceStorage.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/Texture/TextureLoader.h"

namespace Framework {
namespace Utility {

TextureResourceStorage::TextureResourceStorage()
    :mTextureLoader(std::make_unique<Graphics::TextureLoader>()) {}

TextureResourceStorage::~TextureResourceStorage() {}

void TextureResourceStorage::importResource(Define::TextureType type, const std::string& filepath) {
    if (isExist(type))return;
    mResources.emplace(type, mTextureLoader->load(Define::Path::getInstance().texture() + filepath));
}

} //Utility 
} //Framework 
