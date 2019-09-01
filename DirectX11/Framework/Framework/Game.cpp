#include "Game.h"

//メモリリーク検出
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h> 
#include <crtdbg.h>  

#include <Windows.h>
#include "Framework/Device/GameDevice.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Resource/ResourceInitializer.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Input/Mouse.h"
#include "Framework/Window/Window.h"
#include "Framework/Utility/Time.h"
#include "Framework/Define/Game.h"

namespace Framework {

Game::Game(const Math::Vector2& screenSize, bool isFullScreen, float fps)
    :mGameDevice(Device::GameDevice::getInstance()),
    mScreenSize(screenSize),
    mIsFullScreen(isFullScreen),
    mFPS(fps) {
    //メモリリーク検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

Game::~Game() {}

int Game::run() {
    if (!init()) {
        return -1;
    }
    MSG msg = {};
    //メインループ
    while (true) {
        if (!isRunning()) {
            break;
        }
        if (mGameDevice.isEnd()) {
            break;
        }
        //メッセージがあれば処理する
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            double start = Utility::Time::getInstance().mFPSCounter.getTime();
            update(1.0f / mFPS);
            draw();
            double end = Utility::Time::getInstance().mFPSCounter.getTime();
            double diff = end - start;
            double target = 1000.0 / Define::Game::FPS;
            double wait = target - diff;
            MY_DEBUG_LOG(Utility::StringBuilder("diff") << diff);
            MY_DEBUG_LOG(Utility::StringBuilder("target") << target);
            MY_DEBUG_LOG(Utility::StringBuilder("wait") << wait);
            if (wait > 0) {
                timeBeginPeriod(1);
                Sleep(wait);
                timeEndPeriod(1);
            }
            double fps = Utility::Time::getInstance().mFPSCounter.getFPS();
            MY_DEBUG_LOG(Utility::StringBuilder("fps") << fps);
        }
    }

    finalize();
    return 0;
}

bool Game::init() {
    Utility::ResourceManager& resManager = Utility::ResourceManager::getInstance();
    (void)Utility::ResourceInitializeOnStart(resManager);
    mGameDevice.initialize();
    return true;
}

void Game::finalize() {
    mGameDevice.finalize();
}

bool Game::isRunning() {
    return !mGameDevice.getInputManager()->getKeyboard().getKeyDown(Input::KeyCode::Escape);
}

} //Framework 
