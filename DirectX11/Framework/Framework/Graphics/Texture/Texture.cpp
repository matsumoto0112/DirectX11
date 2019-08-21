#include "Texture.h"
#include "Framework/Graphics/Shader/ShaderInputType.h"
#include "Framework/Graphics/Shader/ShaderResourceView.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

Texture::Texture(Texture2DPtr texture2D, SRVPtr srv, int width, int height)
    :mTexture2D(texture2D),
    mSRV(srv),
    mWidth(width),
    mHeight(height) {}

Texture::~Texture() {}

void Texture::setData(ShaderInputType inputType, UINT slotNum) const {
    switch (inputType) {
    case ShaderInputType::Vertex:
        Utility::getContext()->VSSetShaderResources(
            slotNum, 1, mSRV->getShaderResourceView().GetAddressOf());
        break;
    case ShaderInputType::Pixel:
        Utility::getContext()->PSSetShaderResources(
            slotNum, 1, mSRV->getShaderResourceView().GetAddressOf());
        break;
    default:
        MY_ASSERTION(false, "どちらかのシェーダーを選択してください。");
        break;
    }
}

int Texture::getWidth() const {
    return mWidth;
}

int Texture::getHeight() const {
    return mHeight;
}

} //Graphics 
} //Framework 
