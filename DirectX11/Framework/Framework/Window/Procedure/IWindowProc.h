#pragma once
#include <Windows.h>
namespace Framework {
namespace Window {

/**
* @class IWindowProc
* @brief �E�B���h�E�v���V�[�W���C���^�[�t�F�[�X
*/
class IWindowProc {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual  ~IWindowProc() = default;
    /**
    * @brief �E�B���h�E�v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) = 0;
};
} //Window 
} //Framework 
