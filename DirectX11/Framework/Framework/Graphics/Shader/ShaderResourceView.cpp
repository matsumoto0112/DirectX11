#include "ShaderResourceView.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

ShaderResourceView::ShaderResourceView(const TextureBuffer& texture) {
    D3D11_SHADER_RESOURCE_VIEW_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels = 1;

    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateShaderResourceView(texture.getBuffer().Get(),
        &desc, &mShaderResourceView);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "ShaderResourceView作成失敗");
    }
}

ShaderResourceView::ShaderResourceView(const TextureBuffer& texture, const D3D11_SHADER_RESOURCE_VIEW_DESC& desc) {
    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateShaderResourceView(texture.getBuffer().Get(),
        &desc, &mShaderResourceView);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "ShaderResourceView作成失敗");
    }
}

ShaderResourceView::ShaderResourceView(const TextureBuffer& texture, D3D11_SHADER_RESOURCE_VIEW_DESC* descPtr) {
    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateShaderResourceView(texture.getBuffer().Get(),
        descPtr, &mShaderResourceView);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "ShaderResourceView作成失敗");
    }
}

ShaderResourceView::~ShaderResourceView() {}

} //Graphics 
} //Framework 
