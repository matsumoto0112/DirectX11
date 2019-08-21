#include "Framework/Game.h"
#include <memory>
#include <iostream>
#include "Framework/Graphics/DirectX11GraphicsDevice.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Device/GameDevice.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Define/Window.h"
#include "Framework/Window/Window.h"
#include "Framework/Window/Procedure/CloseProc.h"
#include "Framework/Window/Procedure/DestroyProc.h"
#include "Framework/Graphics/String/TextureString.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Input/Mouse.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/GraphicsDevice.h"
#include "Framework/Graphics/RenderingManager.h"
#include "Framework/Utility/ImGUI/Window.h"
#include "Framework/Utility/ImGUI/Button.h"
#include "Framework/Scene/Manager.h"
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