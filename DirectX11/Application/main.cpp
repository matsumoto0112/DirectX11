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
#include "Source/Scene/Impl/ComputeShader.h"
#include "Source/Scene/Impl/RandomColorParticle.h"
#include "Source/Scene/Impl/BlackholeParticle.h"
#include "Source/Scene/Impl/FallParticle.h"
#include "Source/Scene/Impl/FallBounceParticle.h"
#include "Source/Scene/Impl/FallBounceRotateParticle.h"

using namespace Framework;

#define ADD_SCENE_JUMP_BUTTON(name,type){ \
    std::shared_ptr<ImGUI::Button> btn = std::make_shared<ImGUI::Button>(#name,[&](){ \
        mSceneManager->loadScene(type); \
    }); \
    mSceneJumpWindow->addItem(btn); \
}

class MyGame : public Game {
public:
    MyGame() :Game(Math::Vector2((float)Define::Window::WIDTH, (float)Define::Window::HEIGHT), false) {};
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
        //mSceneManager->registerScene(Define::SceneType::MainPlay, std::make_unique<Main>());
        //mSceneManager->registerScene(Define::SceneType::ParticleTest, std::make_unique<ParticleTest>());
        //mSceneManager->registerScene(Define::SceneType::ComputeShader, std::make_unique<ComputeShader>());
        //mSceneManager->registerScene(Define::SceneType::RandomColorParticle, std::make_unique<RandomColorParticle>());

        using Define::SceneType;
        mSceneManager->registerScene(SceneType::BlackholeParticle, std::make_unique<BlackholeParticle>());
        mSceneManager->registerScene(SceneType::FallParticle, std::make_unique<FallParticle>());
        mSceneManager->registerScene(SceneType::FallBounceParticle, std::make_unique<FallBounceParticle>());
        mSceneManager->registerScene(SceneType::FallBounceRotateParticle, std::make_unique<FallBounceRotateParticle>());
        mSceneManager->loadScene(SceneType::FallBounceRotateParticle);

        mSceneJumpWindow = std::make_unique<ImGUI::Window>("Jumper");
        ADD_SCENE_JUMP_BUTTON(BlackholeParticle, SceneType::BlackholeParticle);
        ADD_SCENE_JUMP_BUTTON(FallParticle, SceneType::FallParticle);
        ADD_SCENE_JUMP_BUTTON(FallBounceParticle, SceneType::FallBounceParticle);
        ADD_SCENE_JUMP_BUTTON(FallBounceRotateParticle, SceneType::FallBounceRotateParticle);

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
        renderer->begin();
        mSceneManager->draw(renderer);

        mSceneJumpWindow->draw();
        SetWindowText(mGameDevice.getWindow()->getHWND(), Utility::StringBuilder("") << Utility::Time::getInstance().getCurrentFPS());
        mGameDevice.getRenderingManager()->drawEnd();
        ATLASSERT(_CrtCheckMemory());
    }
    virtual void finalize() override {
        Game::finalize();
    }
private:
    std::unique_ptr<Scene::Manager> mSceneManager;
    std::unique_ptr<ImGUI::Window> mSceneJumpWindow;
};

int main() {
    try {
        MyGame().run();
    }
    catch (const std::exception& e) {
        MY_ERROR_WINDOW(false, e.what());
    }
}