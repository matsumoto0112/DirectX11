#include "ImGUIProc.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Framework {
namespace Window {

ImGUIProc::~ImGUIProc() { }

LRESULT ImGUIProc::wndProc(HWND hWnd, UINT msg,
    WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
        *isReturn = TRUE;
    }
    return 0L;
}

} //Window 
} //Framework 
