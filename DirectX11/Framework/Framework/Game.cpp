#include "Game.h"

//メモリリーク検出
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h> 
#include <crtdbg.h>  

#include <Windows.h>
#include "Framework/Device/GameDevice.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Input/Mouse.h"
#include "Framework/Window/Window.h"
#include "Framework/Utility/Time.h"
#include "Framework/Define/Game.h"

namespace Framework {

Game::Game(const Math::Vector2& screenSize, const std::string& title, bool isFullScreen, float fps)
    : mScreenSize(screenSize),
    mIsFullScreen(isFullScreen),
    mFPS(fps) {
    //メモリリーク検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Device::GameDevice::getInstance()->initialize(screenSize, title);
}

Game::~Game() { }

int Game::run() {
    if (!init()) {
        return -1;
    }

    //タイマーの初期化をここでする
    //リソースの読み込みなどで時間がかかっているため
    Utility::Time::getInstance()->init(mFPS);
    Utility::Time::getInstance()->startFrame();
    Utility::Time::getInstance()->endFrame();

    MSG msg = {};
    //メインループ
    while (true) {
        if (!isRunning()) {
            break;
        }
        if (Device::GameDevice::getInstance()->isEnd()) {
            break;
        }
        //メッセージがあれば処理する
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //else {
        //    Utility::Time::getInstance()->startFrame();
        //    update();
        //    draw();
        //    Utility::Time::getInstance()->endFrame();
        //    Utility::Time::getInstance()->wait();
        //}
    }

    finalize();
    return 0;
}

bool Game::init() {
    return true;
}

void Game::finalize() {
    Device::GameDevice::getInstance()->finalize();
}

bool Game::isRunning() {
    return !Device::GameDevice::getInstance()->getInputManager()->getKeyboard().getKeyDown(Input::KeyCode::Escape);
}

} //Framework 
