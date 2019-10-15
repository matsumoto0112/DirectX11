#include "PaintProc.h"
namespace Framework {
namespace Window {

PaintProc::PaintProc(PerFrameFunc perFrameFunc)
    : mPerFrameFunc(perFrameFunc) { }

PaintProc::~PaintProc() { }

LRESULT PaintProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    switch (msg) {
    case WM_PAINT:
        *isReturn = TRUE;
        mPerFrameFunc();
        break;
    }
    return 0L;
}

} //Window 
} //Framework 
