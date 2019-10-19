#include "GraphicsDevice.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace Graphics {

GraphicsDevice::GraphicsDevice(HWND hWnd, UINT width, UINT height, bool isFullScreen)
    :mDirectX11Device(std::make_unique<DirectX11GraphicsDevice>(
        hWnd, width, height, isFullScreen)) { }

GraphicsDevice::~GraphicsDevice() { }

void GraphicsDevice::drawBegin() {

    mDirectX11Device->getContext()->ClearState();
}

void GraphicsDevice::drawEnd() {
    mDirectX11Device->present(0);
}

void GraphicsDevice::cleanup() {
    mDirectX11Device->getContext()->ClearState();
}

} //Graphics 
} //Framework 