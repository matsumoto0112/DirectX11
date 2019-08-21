#pragma once

#include "Framework/Window/Procedure/IWindowProc.h"

namespace Framework {
namespace Window {
/**
* @class DestroyProc
* @brief �E�B���h�E���j�������Ƃ��ɌĂ΂��v���V�[�W��
*/
class DestroyProc :public IWindowProc{
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~DestroyProc();
    /**
    * @brief �E�B���h�E�v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
};

} //Window 
} //Framework 
