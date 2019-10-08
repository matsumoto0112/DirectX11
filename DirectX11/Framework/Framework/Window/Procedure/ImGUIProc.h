#pragma once

#include "Framework/Window/Procedure/IWindowProc.h"

namespace Framework {
namespace Window {

/**
* @class ImGUIProc
* @brief ImGUI用プロシージャ
*/
class ImGUIProc :public IWindowProc {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~ImGUIProc();
    /**
    * @brief ウィンドウプロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
};
} //Window 
} //Framework 
