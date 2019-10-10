#include "DX11InterfaceAccessor.h"
#include "Framework/Device/GameDevice.h"

namespace Framework {
namespace Graphics {

ComPtr<ID3D11Device> DX11InterfaceAccessor::getDevice() {
    return nullptr;
}

ComPtr<ID3D11DeviceContext> DX11InterfaceAccessor::getContext() {
    return ComPtr<ID3D11DeviceContext>();
}

} //Graphics 
} //Framework 
