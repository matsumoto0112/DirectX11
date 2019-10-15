#include "Texture.h"
#include "Framework/Graphics/Resource/ShaderInputType.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

Texture::Texture(Texture2DPtr texture2D, SRVPtr srv)
    :mTexture2D(texture2D),
    mSRV(srv) {
    D3D11_TEXTURE2D_DESC desc;
    mTexture2D->getTexture()->GetDesc(&desc);
    mWidth = static_cast<int>(desc.Width);
    mHeight = static_cast<int>(desc.Height);
}

Texture::~Texture() { }

void Texture::setData(ShaderInputType inputType, UINT slotNum) const {
    mSRV->set(inputType, slotNum);
}

int Texture::getWidth() const {
    return mWidth;
}

int Texture::getHeight() const {
    return mHeight;
}

} //Graphics 
} //Framework 
