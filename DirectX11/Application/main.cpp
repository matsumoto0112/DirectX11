#include "Game.h"
#include <memory>
#include <iostream>
#include "Graphics/DirectX11GraphicsDevice.h"
#include "Math/Vector2.h"
#include "Device/GameDevice.h"
#include "Utility/Debug.h"
#include "Define/Window.h"
#include "Window/Window.h"
#include "Window/Procedure/CloseProc.h"
#include "Window/Procedure/DestroyProc.h"
#include "Graphics/String/TextureString.h"
#include "Input/InputManager.h"
#include "Input/Mouse.h"
#include "Define/Path.h"
#include "Graphics/GraphicsDevice.h"
#include "Graphics/RenderingManager.h"
#include "Utility/ImGUI/Window.h"
#include "Utility/ImGUI/Button.h"
#include "Scene/Manager.h"
#include "Source/Scene/Impl/Title.h"

using namespace Framework;

class MyGame : public Game {
public:
    MyGame() :Game(Math::Vector2((float)Define::Window::WIDTH, (float)Define::Window::HEIGHT)) {};
    ~MyGame() {};
private:
    virtual bool init() override {
        if (!Game::init()) {
            return false;
        }
        auto& window = mGameDevice.getWindow();
        HWND hWnd = window.getHWND();
        window.setProcedureEvent(new Window::DestroyProc());
        window.setProcedureEvent(new Window::CloseProc());

        mSceneManager = std::make_unique<Scene::Manager>();
        mSceneManager->registerScene(Define::SceneType::Title, std::make_unique<Title>());
        mSceneManager->loadScene(Define::SceneType::Title);
        return true;
    }
    virtual void update(float deltaTime) override {
        mGameDevice.update();
        mSceneManager->update(deltaTime);
    }
    virtual void draw() override {
        mGameDevice.getRenderingManager()->drawBegin();

        mSceneManager->draw();

        mGameDevice.getRenderingManager()->drawEnd();
    }
    virtual void finalize() override {
        Game::finalize();
    }
private:
    std::unique_ptr<Scene::Manager> mSceneManager;
};

int main() {
    try {
        MyGame().run();
    }
    catch (const std::exception& e) {
        MY_ERROR_WINDOW(false, e.what());
    }
}