#include "Texture2D.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

Texture2D::Texture2D(const D3D11_TEXTURE2D_DESC* texDesc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateTexture2D(texDesc, nullptr, &mTexture2D));
}

Texture2D::Texture2D(ComPtr<ID3D11Texture2D> texture)
    :mTexture2D(texture) { }

Texture2D::~Texture2D() { }


} //Graphics 
} //Framework 
