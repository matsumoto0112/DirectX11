#pragma once
#include <functional>
#include "Framework/Window/Procedure/IWindowProc.h"

namespace Framework {
namespace Window {

class PaintProc : public IWindowProc {
    using PerFrameFunc = std::function<void(void)>;
public:
    /**
    * @brief コンストラクタ
    * @param perFrameFunc フレーム単位で実行する関数
    */
    PaintProc(PerFrameFunc perFrameFunc);
    /**
    * @brief デストラクタ
    */
    virtual ~PaintProc();
    /**
    * @brief ウィンドウプロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
private:
    PerFrameFunc mPerFrameFunc;
};

} //Window 
} //Framework 
