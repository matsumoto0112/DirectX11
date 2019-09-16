#include "Framework/Game.h"
#include <atlbase.h>
#include <iostream>
#include <memory>
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
#include "Source/Scene/Impl/Main.h"
#include "Framework/Utility/Time.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Source/Scene/Impl/ParticleTest.h"
#include <atlstr.h>

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
        auto window = mGameDevice.getWindow();
        window->setProcedureEvent(new Window::DestroyProc());
        window->setProcedureEvent(new Window::CloseProc());

        mSceneManager = std::make_unique<Scene::Manager>();
        //mSceneManager->registerScene(Define::SceneType::Title, std::make_unique<Title>());
        mSceneManager->registerScene(Define::SceneType::MainPlay, std::make_unique<Main>());
        mSceneManager->registerScene(Define::SceneType::ParticleTest, std::make_unique<ParticleTest>());
        mSceneManager->loadScene(Define::SceneType::MainPlay);

        ATLASSERT(_CrtCheckMemory());
        return true;
    }
    virtual void update() override {
        mGameDevice.update();
        mSceneManager->update();
        ATLASSERT(_CrtCheckMemory());
    }
    virtual void draw() override {
        Graphics::IRenderer* renderer = mGameDevice.getRenderingManager()->drawBegin();
        //renderer->setBackColor(Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
        
        renderer->begin();
        mSceneManager->draw(renderer);

        mGameDevice.getRenderingManager()->drawEnd();

        Utility::StringBuilder sb("");
        float fps = Utility::Time::getInstance().getCurrentFPS();
        sb << fps;
        SetWindowText(mGameDevice.getWindow()->getHWND(), CString(sb.getStr().c_str()));

        ATLASSERT(_CrtCheckMemory());
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