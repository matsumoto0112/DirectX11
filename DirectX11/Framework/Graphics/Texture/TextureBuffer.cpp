#include "TextureBuffer.h"
#include "Graphics/DirectX11GraphicsDevice.h"
#include "Utility/Debug.h"
#include "Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

Graphics::TextureBuffer::TextureBuffer(DirectX11GraphicsDevice& device) {
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = device.getSwapChain();
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&mTextureBuffer);
    D3D11_TEXTURE2D_DESC desc;
    mTextureBuffer->GetDesc(&desc);
    mSize.x = (float)desc.Width;
    mSize.y = (float)desc.Height;
}

TextureBuffer::TextureBuffer(const D3D11_TEXTURE2D_DESC& desc)
    :mSize((float)desc.Width, (float)desc.Height) {
    HRESULT hr = Utility::getDevice()->CreateTexture2D(&desc, nullptr, &mTextureBuffer);
    MY_ASSERTION(SUCCEEDED(hr), "テクスチャバッファの作成に失敗しました。");
}

TextureBuffer::TextureBuffer(const D3D11_TEXTURE2D_DESC& desc,
    const D3D11_SUBRESOURCE_DATA& sub)
    : mSize((float)desc.Width, (float)desc.Height) {
    HRESULT hr = Utility::getDevice()->CreateTexture2D(&desc, &sub, &mTextureBuffer);
    MY_ASSERTION(SUCCEEDED(hr), "テクスチャバッファの作成に失敗しました。");
}

Graphics::TextureBuffer::~TextureBuffer() {}

} //Graphics 
} //Framework 
