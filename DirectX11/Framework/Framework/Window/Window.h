#pragma once 

#include <Windows.h>
#include <memory>
#include <string>
#include <functional>
#include "Framework/Math/Vector2.h"

namespace Framework {
namespace Window {

class IWindowProc;
/**
* @class Window
* @brief 1ウィンドウの管理クラス
*/
class Window {
private:
    using Vec2 = Math::Vector2;
public:
    /**
    * @brief コンストラクタ
    * @param clientSize クライアント領域の大きさ
    * @param position ウィンドウの座標
    * @param windowTitle ウィンドウのタイトル
    * @param toWindowEndApplicationQuit ウィンドウ終了時にアプリケーションを終了させるか
    */
    Window(const Vec2& clientSize, const Vec2& position,
        const std::string& windowTitle, bool toWindowEndApplicationQuit);
    /**
    * @brief デストラクタ
    */
    ~Window();
    /**
    * @brief ウィンドウの大きさと座標を設定
    * @param clientSize クライアント領域の大きさ
    * @param position 座標
    */
    void setWindowSizeAndPosition(const Vec2& clientSize, const Vec2& position);
    /**
    * @brief ウィンドウの破棄
    */
    void quit();
    /**
    * @brief ウィンドウハンドルの取得
    * @return ウィンドウハンドル
    */
    HWND getHWND() const;
    /**
    * @brief ウィンドウが閉じられたか
    */
    bool isClosed() const;
    /**
    * @brief ウィンドウプロシージャを追加
    * @param proc 追加するプロシージャ
    */
    void setProcedureEvent(IWindowProc* proc);
    /**
    * @brief ウィンドウがアクティブ状態か
    */
    bool isActive() const;

    void setActive(bool activeFlag);
private:
    HWND mHWnd; //!< ウィンドウハンドル
    Vec2 mClientSize; //!< クライアント領域の大きさ
};

} //Window 
} //Framework 