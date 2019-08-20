#include "Keyboard.h"
#include "Input/KeyCode.h"
#include "Utility/Debug.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace {
int getIndex(Framework::Input::KeyCode key) {
    return static_cast<int>(key);
}
}
namespace Framework {
namespace Input {

Keyboard::Keyboard(HWND hWnd)
    :mCurrentKeys(), mPrevKeys() {}

Keyboard::~Keyboard() {}

void Keyboard::update() {
    std::copy(mCurrentKeys.begin(), mCurrentKeys.end(), mPrevKeys.begin());
    GetKeyboardState(mCurrentKeys.data());
}

bool Keyboard::getKey(KeyCode key) const {
    return checkKeyDown(mCurrentKeys, key);
}

bool Keyboard::getKeyDown(KeyCode key) const {
    bool prev = checkKeyDown(mPrevKeys, key);
    bool cur = checkKeyDown(mCurrentKeys, key);
    return !prev && cur;
}

bool Keyboard::getKeyUp(KeyCode key) const {
    bool prev = checkKeyDown(mPrevKeys, key);
    bool cur = checkKeyDown(mCurrentKeys, key);
    return prev && !cur;
}

bool Keyboard::checkKeyDown(const KeyInfo& keys, KeyCode key) const {
    return (keys[getIndex(key)] & 0x80) != 0;
}

} //Input 
} //Framework
