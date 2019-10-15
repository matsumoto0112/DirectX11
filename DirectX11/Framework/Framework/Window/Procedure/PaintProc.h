#pragma once
#include <functional>
#include "Framework/Window/Procedure/IWindowProc.h"

namespace Framework {
namespace Window {

class PaintProc : public IWindowProc {
    using PerFrameFunc = std::function<void(void)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param perFrameFunc �t���[���P�ʂŎ��s����֐�
    */
    PaintProc(PerFrameFunc perFrameFunc);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~PaintProc();
    /**
    * @brief �E�B���h�E�v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
private:
    PerFrameFunc mPerFrameFunc;
};

} //Window 
} //Framework 
