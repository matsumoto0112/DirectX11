#include "OftenUsed.h"
#include "Framework/Device/GameDevice.h"
#include "Framework/Window/Window.h"

namespace Framework {
namespace Utility {

HWND getMainHWND() {
    return Device::GameDevice::getInstance().getWindow()->getHWND();
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

Graphics::CameraManager* getCameraManager() {
    return getRenderingManager()->getCameraManager();
}

Input::InputManager* getInputManager() {
    return Device::GameDevice::getInstance().getInputManager();
}

Utility::ResourceManager* getResourceManager() {
    return &Utility::ResourceManager::getInstance();
}

} //Graphics 
} //Framework 
