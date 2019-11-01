#include "Framework/Game.h"
#include <atlbase.h>
#include <iostream>
#include <memory>
//#include "Framework/Graphics/DirectX11GraphicsDevice.h"
//#include "Framework/Math/Vector2.h"
//#include "Framework/Device/GameDevice.h"
//#include "Framework/Utility/Debug.h"
//#include "Framework/Window/Window.h"
//#include "Framework/Window/Procedure/PaintProc.h"
//#include "Framework/Window/Procedure/CloseProc.h"
//#include "Framework/Window/Procedure/DestroyProc.h"
//#include "Framework/Window/Procedure/ImGUIProc.h"
//#include "Framework/Graphics/String/TextureString.h"
//#include "Framework/Input/InputManager.h"
//#include "Framework/Input/Mouse.h"
//#include "Framework/Define/Path.h"
//#include "Framework/Graphics/GraphicsDevice.h"
//////#include "Framework/Graphics/RenderingManager.h"
//#include "Framework/Utility/ImGUI/Window.h"
//#include "Framework/Utility/ImGUI/Button.h"
//#include "Framework/Scene/Manager.h"
//#include "Framework/Utility/Time.h"
//#include "Framework/Graphics/Renderer/Pipeline.h"
////#include "Source/Scene/Impl/GPUParticle/BlackholeParticle.h"
////#include "Source/Scene/Impl/GPUParticle/Firefly.h"
////#include "Source/Scene/Impl/GPUParticle/FallParticle.h"
////#include "Source/Scene/Impl/GPUParticle/IceBlock.h"
////#include "Source/Scene/Impl/GPUParticle/WormholeParticle.h"
////#include "Source/Scene/Impl/Shadow/Shadow.h"
////#include "Source/Scene/Impl/RenderModel.h"
//#include "Framework/Define/Config.h"
////#include "Source/Scene/Impl/Shadow/DirLight.h"
////#include "Source/Scene/Impl/Light/NormalizedLambert.h"
////#include "Source/Scene/Impl/Light/NormalizedLambert_NewRendering.h"
//#include "Source/Scene/Impl/TestScene.h"
//#include "Framework/Graphics/DX11RenderingManager.h"
//
#pragma comment(linker, "/entry:mainCRTStartup")
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dCompiler.lib")

using namespace Framework;

#define ADD_SCENE_JUMP_BUTTON(name,type){ \
    std::shared_ptr<ImGUI::Button> btn = std::make_shared<ImGUI::Button>(#name,[&](){ \
        mSceneManager->loadScene(type); \
    }); \
    mGlobalWindow->addItem(btn); \
}
#define BUILD_SCENE(name,type,scene) { \
    mSceneManager->registerScene(type, scene); \
    ADD_SCENE_JUMP_BUTTON(name,type); \
}

class MyGame : public Game {
public:
    MyGame() :Game(Define::Config::getInstance()->getSize(), "Game", false) { };
    ~MyGame() { };
private:
    virtual bool init() override {
        if (!Game::init()) {
            return false;
        }
        //auto window = Device::GameDevice::getInstance()->getWindow();
        //window->setProcedureEvent(new Window::ImGUIProc());
        //window->setProcedureEvent(new Window::DestroyProc());

        ////毎フレーム実行する関数定義
        //window->setProcedureEvent(new Window::PaintProc([&]() {
        //    Utility::Time::getInstance()->startFrame();
        //    this->update();
        //    this->draw();
        //    Utility::Time::getInstance()->endFrame();
        //}));

        //window->setProcedureEvent(new Window::CloseProc());
        //Framework::Graphics::DX11RenderingManager::getInstance()->init(window->getHWND(),
        //    Define::Config::getInstance()->getWidth(), Define::Config::getInstance()->getHeight(), 2, false);

        //mSceneManager = std::make_unique<Scene::Manager>();

        //{
        //    using Define::SceneType;

        //    mGlobalWindow = std::make_unique<ImGUI::Window>("Jumper");
        //    mFPSText = std::make_shared<ImGUI::Text>("FPS");
        //    mGlobalWindow->addItem(mFPSText);
        //    //BUILD_SCENE(FireFly, SceneType::Firefly, std::make_unique<Firefly>());
        //    //BUILD_SCENE(BlackholeParticle, SceneType::BlackholeParticle, std::make_unique<BlackholeParticle>());
        //    //BUILD_SCENE(FallParticle, SceneType::FallParticle, std::make_unique<FallParticle>());
        //    //BUILD_SCENE(IceBlock, SceneType::IceBlock, std::make_unique<IceBlock>());
        //    //BUILD_SCENE(WormholeParticle, SceneType::WormholeParticle, std::make_unique<WormholeParticle>());
        //    //BUILD_SCENE(Shadow, SceneType::Shadow, std::make_unique<Shadow>());
        //    //BUILD_SCENE(RenderModel, SceneType::RenderModel, std::make_unique<RenderModel>());
        //    //BUILD_SCENE(DirLight, SceneType::DirLight, std::make_unique<DirLight>());
        //    //BUILD_SCENE(NormalizedLambert, SceneType::NormalizedLambert, std::make_unique<NormalizedLambert>());
        //    //BUILD_SCENE(NormalizedLambert, SceneType::NormalizedLambert, std::make_unique<NormalizedLambert_NewRendering>());
        //    BUILD_SCENE(TestScene, SceneType::TestScene, std::make_unique<TestScene>());
        //    mSceneManager->loadScene(SceneType::TestScene);

        //}

        ATLASSERT(_CrtCheckMemory());
        return true;
    }
    virtual void update() override {
        //Device::GameDevice::getInstance()->update();
        //mSceneManager->update();
        //mFPSText->setText(Utility::StringBuilder("FPS:") << Utility::Time::getInstance()->getCurrentFPS());
        //ATLASSERT(_CrtCheckMemory());
    }
    virtual void draw() override {
        //Graphics::DX11RenderingManager::getInstance()->beginFrame();
        ////Graphics::IRenderer* renderer = Device::GameDevice::getInstance()->getRenderingManager()->drawBegin();
        //mSceneManager->draw(nullptr);
        ////mGlobalWindow->draw();
        ////Device::GameDevice::getInstance()->getRenderingManager()->drawEnd();
        //Graphics::DX11RenderingManager::getInstance()->endFrame();
        //ATLASSERT(_CrtCheckMemory());
    }
    virtual void finalize() override {
        Game::finalize();
    }
private:
    //std::unique_ptr<Scene::Manager> mSceneManager;
    //std::unique_ptr<ImGUI::Window> mGlobalWindow;
    //std::shared_ptr<ImGUI::Text> mFPSText;
};

int main() {
    try {
        MyGame().run();
    }
    catch (const std::exception& e) {
        MY_ERROR_WINDOW(false, e.what());
        return -1;
    }
}