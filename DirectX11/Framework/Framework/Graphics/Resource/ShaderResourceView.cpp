#include "ShaderResourceView.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

ShaderResourceView::ShaderResourceView(std::shared_ptr<Texture2D> texture, const D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateShaderResourceView(texture->getTexture().Get(), srvDesc, &mShaderResourceView));
}

ShaderResourceView::~ShaderResourceView() { }

void ShaderResourceView::set(ShaderInputType inputType, UINT registerNum) {
    if ((inputType & ShaderInputType::Vertex) == ShaderInputType::Vertex) {
        DX11InterfaceAccessor::getContext()->VSSetShaderResources(registerNum, 1, mShaderResourceView.GetAddressOf());
    }
    if ((inputType & ShaderInputType::Pixel) == ShaderInputType::Pixel) {
        DX11InterfaceAccessor::getContext()->PSSetShaderResources(registerNum, 1, mShaderResourceView.GetAddressOf());
    }
    if ((inputType & ShaderInputType::Geometory) == ShaderInputType::Geometory) {
        DX11InterfaceAccessor::getContext()->GSSetShaderResources(registerNum, 1, mShaderResourceView.GetAddressOf());
    }
    if ((inputType & ShaderInputType::Compute) == ShaderInputType::Compute) {
        DX11InterfaceAccessor::getContext()->CSSetShaderResources(registerNum, 1, mShaderResourceView.GetAddressOf());
    }
}

} //Graphics 
} //Framework 
