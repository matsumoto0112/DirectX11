#include "DX11InterfaceAccessor.h"
#include "Framework/Device/GameDevice.h"

namespace Framework {
namespace Graphics {

ComPtr<ID3D11Device> DX11InterfaceAccessor::getDevice() {
    return Device::GameDevice::getInstance()->getRenderingManager()->getGraphicsDevice()->getDirectX11GraphicsDevice()->getDevice();
}

ComPtr<ID3D11DeviceContext> DX11InterfaceAccessor::getContext() {
    return Device::GameDevice::getInstance()->getRenderingManager()->getGraphicsDevice()->getDirectX11GraphicsDevice()->getContext();
}

} //Graphics 
} //Framework 
