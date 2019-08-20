#pragma once
#include <Windows.h>
#include <vector>
#include <memory>
#include "Window/Procedure/IWindowProc.h"

namespace Framework {
namespace Window {

/**
* @class WindowProcedures
* @brief �E�B���h�E�v���V�[�W���֐��̒�`
*/
class WindowProcedures {
public:
    /**
    * v���C���E�B���h�E�̃E�B���h�E�v���V�[�W��
    * @param hWnd ���b�Z�[�W�̔��������E�B���h�E�n���h��
    * @param message ���b�Z�[�W�̎��
    * @param wParam �p�����[�^1
    * @param lParam �p�����[�^2
    * @return LRESULT �I���R�[�h
    */
    static LRESULT CALLBACK mainWndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);

    /**
    * @brief �T�u�E�B���h�E�̃E�B���h�E�v���V�[�W��
    * @param hWnd ���b�Z�[�W�̔��������E�B���h�E�n���h��
    * @param message ���b�Z�[�W�̎��
    * @param wParam �p�����[�^1
    * @param lParam �p�����[�^2
    * @return LRESULT �I���R�[�h
    */
    static LRESULT CALLBACK subWndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);
public:
    static std::vector<std::unique_ptr<IWindowProc>> mWindowProcs; //!< �E�B���h�E�v���V�[�W�����X�g
};

} //Window 
} //Framework 