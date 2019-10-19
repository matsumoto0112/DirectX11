#include "ShaderResourceView.h"
//#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
    namespace Graphics {

        ShaderResourceView::ShaderResourceView(ID3D11Device* device, std::shared_ptr<Texture2D> texture, const D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc) {
            throwIfFailed(device->CreateShaderResourceView(texture->getTexture().Get(), srvDesc, &mShaderResourceView));
        }

        ShaderResourceView::~ShaderResourceView() { }

        void ShaderResourceView::set(ID3D11DeviceContext* context, ShaderInputType inputType, UINT registerNum) {
            if ((inputType & ShaderInputType::Vertex) == ShaderInputType::Vertex) {
                context->VSSetShaderResources(registerNum, 1, mShaderResourceView.GetAddressOf());
            }
            if ((inputType & ShaderInputType::Pixel) == ShaderInputType::Pixel) {
                context->PSSetShaderResources(registerNum, 1, mShaderResourceView.GetAddressOf());
            }
            if ((inputType & ShaderInputType::Geometory) == ShaderInputType::Geometory) {
                context->GSSetShaderResources(registerNum, 1, mShaderResourceView.GetAddressOf());
            }
            if ((inputType & ShaderInputType::Compute) == ShaderInputType::Compute) {
                context->CSSetShaderResources(registerNum, 1, mShaderResourceView.GetAddressOf());
            }
        }

    } //Graphics 
} //Framework 
