#include "GameDevice.h"
#include "Framework/Define/Config.h"
#include "Framework/Define/Game.h"
#include "Framework/Graphics/GraphicsDevice.h"
#include "Framework/Graphics/RenderingManager.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Window/Window.h"

namespace Framework {
namespace Device {

Window::Window* GameDevice::getWindow() const {
    return mMainWindow.get();
}

Graphics::RenderingManager* GameDevice::getRenderingManager() const {
    return mRenderingManager.get();
}

Input::InputManager* GameDevice::getInputManager() const {
    return mInputManager.get();
}

void GameDevice::update() {
    mInputManager->update();
}

bool GameDevice::isEnd() const {
    return mMainWindow->isClosed();
}

void GameDevice::finalize() {
    mMainWindow->quit();
}

void GameDevice::initialize(const Math::Vector2& screenSize, const std::string& title) {
    mMainWindow = std::make_unique<Window::Window>(
        screenSize,
        Math::Vector2(0, 0),
        title,
        true);

    mRenderingManager = std::make_unique<Graphics::RenderingManager>(
        mMainWindow->getHWND(),
        static_cast<UINT>(screenSize.x),
        static_cast<UINT>(screenSize.y),
        false);

    mInputManager = std::make_unique<Input::InputManager>(*mMainWindow);

    mRenderingManager->initialize();
}

GameDevice::GameDevice() { }

GameDevice::~GameDevice() { }


} //Device 
} //Framework 