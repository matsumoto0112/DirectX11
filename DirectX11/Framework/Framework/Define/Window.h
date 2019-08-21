#pragma once

#include <string>
#include "Framework/Math/Vector2.h"

namespace Define {

/**
* @brief �E�B���h�E����`
*/
class Window {
public:
    static const int WIDTH; //!< ��ʕ�
    static const int HEIGHT; //!< ��ʍ���
    static const std::string TITLE; //!< �E�B���h�E�^�C�g��
public:
    static Framework::Math::Vector2 getSize() {
        return Framework::Math::Vector2((float)WIDTH, (float)HEIGHT);
    }
};

} //Define 