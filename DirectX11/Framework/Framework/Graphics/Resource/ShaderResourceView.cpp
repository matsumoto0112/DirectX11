#include "ShaderResourceView.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

ShaderResourceView::ShaderResourceView(std::shared_ptr<Texture2D> texture, const D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateShaderResourceView(texture->getTexture().Get(), srvDesc, &mShaderResourceView));
}

ShaderResourceView::~ShaderResourceView() { }

} //Graphics 
} //Framework 
