#include "OftenUsed.h"
#include "Device/GameDevice.h"
#include "Window/Window.h"

namespace Framework {
namespace Utility {

HWND getMainHWND() {
    return Device::GameDevice::getInstance().getWindow().getHWND();
}

ImGUI::Manager* getImGUIManager() {
    return getRenderingManager()->getImGUIManager();
}

Graphics::RenderingManager* Utility::getRenderingManager() {
    return Device::GameDevice::getInstance().getRenderingManager();
}

Graphics::ConstantBufferManager* getConstantBufferManager() {
    return getRenderingManager()->getConstantBufferManager();
}

Input::InputManager* getInputManager() {
    return Device::GameDevice::getInstance().getInputManager();
}

} //Graphics 
} //Framework 
