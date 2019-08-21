#pragma once

#include <string>
#include "Framework/Math/Vector2.h"

namespace Define {

/**
* @brief ウィンドウ情報定義
*/
class Window {
public:
    static const int WIDTH; //!< 画面幅
    static const int HEIGHT; //!< 画面高さ
    static const std::string TITLE; //!< ウィンドウタイトル
public:
    static Framework::Math::Vector2 getSize() {
        return Framework::Math::Vector2((float)WIDTH, (float)HEIGHT);
    }
};

} //Define 