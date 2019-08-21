#pragma once

#include "Framework/Window/Procedure/IWindowProc.h"

namespace Framework {
namespace Window {

/**
* @class CloseProc
* @brief �I������Ƃ��ɌĂ΂��v���V�[�W��
*/
class CloseProc :public IWindowProc{
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~CloseProc();
    /**
    * @brief �E�B���h�E�v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
};
} //Window 
} //Framework 
