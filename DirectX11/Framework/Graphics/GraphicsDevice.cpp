#include "GraphicsDevice.h"
#include "Graphics/DirectX11GraphicsDevice.h"
#include "Graphics/Texture/TextureBuffer.h"
#include "Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace Graphics {

GraphicsDevice::GraphicsDevice(HWND hWnd, const Math::Vector2& screenSize, bool isFullScreen)
    :mDirectX11Device(std::make_unique<DirectX11GraphicsDevice>(
        hWnd, static_cast<UINT>(screenSize.x), static_cast<UINT>(screenSize.y), isFullScreen)) {
}

GraphicsDevice::~GraphicsDevice() {}

void GraphicsDevice::drawBegin() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    mDirectX11Device->getContext()->ClearState();
}

void GraphicsDevice::drawEnd() {
    mDirectX11Device->present();
}

void GraphicsDevice::cleanup() {
    mDirectX11Device->getContext()->ClearState();
}

} //Graphics 
} //Framework 