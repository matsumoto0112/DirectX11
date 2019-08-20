#include "WindowProcedures.h"
#include "Utility/ImGUI/ImGUI.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Framework {
namespace Window {

std::vector<std::unique_ptr<IWindowProc>>
WindowProcedures::mWindowProcs = std::vector<std::unique_ptr<IWindowProc>>();

LRESULT WindowProcedures::mainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    BOOL isReturn = FALSE;
    //�擪���珇�Ƀv���V�[�W�������������܂Ń��[�v
    for (auto&& proc : mWindowProcs) {
        LRESULT res = proc->wndProc(hWnd, message, wParam, lParam, &isReturn);
        if (isReturn)return res;
    }
    //����̏������s��
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT WindowProcedures::subWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hWnd, message, wParam, lParam);
}

} //Window 
} //Framework 
