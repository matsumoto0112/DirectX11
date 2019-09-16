#include "GameDevice.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/GraphicsDevice.h"
#include "Framework/Graphics/RenderingManager.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Define/Game.h"
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

void GameDevice::initialize() {
    mRenderingManager->initialize();
}

GameDevice::GameDevice() {
    const Math::Vector2 screenSize(
        static_cast<float>(Define::Window::WIDTH),
        static_cast<float>(Define::Window::HEIGHT));
    mMainWindow = std::make_unique<Window::Window>(
        screenSize,
        Math::Vector2(0, 0),
        Define::Window::TITLE,
        false);

    mRenderingManager = std::make_unique<Graphics::RenderingManager>(
        mMainWindow->getHWND(),
        screenSize,
        false);
    mInputManager = std::make_unique<Input::InputManager>(*mMainWindow);
}

GameDevice::~GameDevice() {}


} //Device 
} //Framework 