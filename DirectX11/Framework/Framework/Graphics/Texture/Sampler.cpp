#include "Sampler.h"
#include <assert.h>
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Resource/ShaderInputType.h"
#include "Framework/Utility/Debug.h"

namespace {

D3D11_TEXTURE_ADDRESS_MODE convert(Framework::Graphics::TextureAddressMode addressMode) {
    using Framework::Graphics::TextureAddressMode;
    switch (addressMode) {
        case TextureAddressMode::Wrap:
            return D3D11_TEXTURE_ADDRESS_WRAP;
        case TextureAddressMode::Clamp:
            return D3D11_TEXTURE_ADDRESS_CLAMP;
        default:
            MY_ASSERTION(false, "不正なテクスチャモードが選択されました");
            return (D3D11_TEXTURE_ADDRESS_MODE)0;
    }
}

D3D11_FILTER convert(Framework::Graphics::TextureFilterMode filterMode) {
    using Framework::Graphics::TextureFilterMode;
    switch (filterMode) {
        case TextureFilterMode::MinMagMipLinear:
            return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        case TextureFilterMode::MinMagMipPoint:
            return D3D11_FILTER_MIN_MAG_MIP_POINT;
        default:
            MY_ASSERTION(false, "不正なフィルタリングモードが選択されました");
            return (D3D11_FILTER)0;
    }
}
}
namespace Framework {
namespace Graphics {

Sampler::Sampler(TextureAddressMode addressMode, TextureFilterMode filterMode) {
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = convert(filterMode);
    D3D11_TEXTURE_ADDRESS_MODE texAddressMode = convert(addressMode);
    sampDesc.AddressU = texAddressMode;
    sampDesc.AddressV = texAddressMode;
    sampDesc.AddressW = texAddressMode;
    sampDesc.MaxAnisotropy = 1;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = -3.402823466e+38F;
    sampDesc.MaxLOD = 3.402823466e+38F;
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateSamplerState(&sampDesc, &mSamplerState));
}

Sampler::Sampler(const D3D11_SAMPLER_DESC& desc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateSamplerState(&desc, &mSamplerState));
}

Sampler::~Sampler() { }

void Sampler::setData(ShaderInputType inputType, UINT slotNumber) {
    switch (inputType) {
        case Graphics::ShaderInputType::Vertex:
            DX11InterfaceAccessor::getContext()->VSSetSamplers(slotNumber, 1, mSamplerState.GetAddressOf());
            break;
        case Graphics::ShaderInputType::Pixel:
            DX11InterfaceAccessor::getContext()->PSSetSamplers(slotNumber, 1, mSamplerState.GetAddressOf());
            break;
        default:
            MY_ASSERTION(false, "未定義のinputTypeが選択されました");
            break;
    }
}

} //Graphics 
} //Framework 
