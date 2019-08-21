#include "DirectX.h"
#include "Framework/Device/GameDevice.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Graphics/GraphicsDevice.h"
#include "Framework/Graphics/RenderingManager.h"

namespace Framework {
namespace Utility {

ID3D11Device* getDevice() {
    return Device::GameDevice::getInstance().getRenderingManager()->getGraphicsDevice()->getDirectX11GraphicsDevice()->getDevice().Get();
}

ID3D11DeviceContext* getContext() {
    return Device::GameDevice::getInstance().getRenderingManager()->getGraphicsDevice()->getDirectX11GraphicsDevice()->getContext().Get();
}

} //Utility 
} //Framework 
