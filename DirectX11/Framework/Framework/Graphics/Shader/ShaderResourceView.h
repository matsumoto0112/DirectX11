#pragma once

#include <memory>
#include <wrl/client.h>
#include <d3d11.h>

namespace Framework {
namespace Graphics {

class DirectX11GraphicsDevice;
class TextureBuffer;

class ShaderResourceView {
public:
    ShaderResourceView(const TextureBuffer& texture);
    ShaderResourceView(const TextureBuffer& texture, const D3D11_SHADER_RESOURCE_VIEW_DESC& desc);
    ShaderResourceView(const TextureBuffer& texture, D3D11_SHADER_RESOURCE_VIEW_DESC* descPtr);
    ~ShaderResourceView();
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> getShaderResourceView() const { return mShaderResourceView; }
private:
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResourceView;
};

} //Graphics 
} //Framework 
