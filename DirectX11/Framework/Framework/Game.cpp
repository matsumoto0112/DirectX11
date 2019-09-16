#include "Game.h"

//���������[�N���o
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
    //���������[�N���o
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

Game::~Game() {}

int Game::run() {
    if (!init()) {
        return -1;
    }

    //�^�C�}�[�̏������������ł���
    //���\�[�X�̓ǂݍ��݂ȂǂŎ��Ԃ��������Ă��邽��
    Utility::Time::getInstance().init(mFPS);
    Utility::Time::getInstance().startFrame();
    Utility::Time::getInstance().endFrame();

    MSG msg = {};
    //���C�����[�v
    while (true) {
        if (!isRunning()) {
            break;
        }
        if (mGameDevice.isEnd()) {
            break;
        }
        //���b�Z�[�W������Ώ�������
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            Utility::Time::getInstance().startFrame();
            update();
            draw();
            Utility::Time::getInstance().endFrame();
            //Utility::Time::getInstance().wait();
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
