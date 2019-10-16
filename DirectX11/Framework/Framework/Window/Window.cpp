#include "Window.h"
#include <atlstr.h>
#include "Framework/Utility/Debug.h"
#include "Framework/Window/WindowProcedures.h"

namespace {
Framework::Math::Vector2 convertWindowSize(HWND hWnd, const Framework::Math::Vector2& clientSize) {
    RECT windowRect; //ウィンドウの大きさ
    RECT clientRect; //クライアント領域の大きさ
    GetWindowRect(hWnd, &windowRect);
    GetClientRect(hWnd, &clientRect);
    //クライアント領域の大きさからウィンドウの大きさに変換
    const float width = clientSize.x + (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left);
    const float height = clientSize.y + (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top);
    return Framework::Math::Vector2(width, height);
}

bool createWindow(HWND* hWnd,
    const Framework::Math::Vector2& clientSize, const Framework::Math::Vector2& position,
    const CString& name, bool toWindowEndApplicationQuit) {
    // ウィンドウクラスのパラメータ設定
    WNDCLASSEX wcex;
    //構造体のサイズ
    wcex.cbSize = sizeof(WNDCLASSEX);
    //ウィンドウスタイル
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    //ウィンドウのメッセージ処理をするコールバック関数の登録
    wcex.lpfnWndProc = Framework::Window::WindowProcedures::mainWndProc;
    //ウインドウクラス構造体の後ろに割り当てる補足バイト数
    wcex.cbClsExtra = 0;
    //ウインドウインスタンスの後ろに割り当てる補足バイト数
    wcex.cbWndExtra = 0;
    //このクラスのためのウインドウプロシージャがあるインスタンスハンドル
    wcex.hInstance = GetModuleHandle(NULL);
    //アイコンのハンドル
    wcex.hIcon = NULL;
    //マウスカーソルのハンドル
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    //ウインドウ背景色
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW - 1);
    //デフォルトメニュー名
    wcex.lpszMenuName = NULL;
    //wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    //ウインドウクラスにつける名前
    wcex.lpszClassName = name;
    //16×16の小さいサイズのアイコン
    wcex.hIconSm = NULL;
    //登録に失敗したら失敗したと返す
    if (!RegisterClassEx(&wcex))
        return false;

    //ウィンドウの大きさを取得
    const Framework::Math::Vector2 windowSize = convertWindowSize(*hWnd, clientSize);
    //ウィンドウの生成    
    *hWnd = CreateWindow(name, name,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        (int)(position.x), (int)(position.y),
        (int)(windowSize.x), (int)(windowSize.y),
        nullptr, nullptr, wcex.hInstance,
        NULL);
    //登録に失敗したら失敗したと返す
    if (!(*hWnd))
        return false;

    //ウィンドウの大きさがリリースモード時に違うことがあるのでここで再指定
    return SetWindowPos(*hWnd, nullptr, (int)position.x, (int)position.y, (int)clientSize.x, (int)clientSize.y, SWP_NOZORDER);;
}
}
namespace Framework {
namespace Window {

Window::Window(const Vec2& clientSize, const Vec2& position, const std::string& windowTitle, bool toWindowEndApplicationQuit)
    :mClientSize(clientSize) {
    bool succeed;
#if UNICODE
    succeed = createWindow(&mHWnd, clientSize, position, CStringW(windowTitle.c_str()), toWindowEndApplicationQuit);
#else
    succeed = createWindow(&mHWnd, clientSize, position, windowTitle.c_str(), toWindowEndApplicationQuit);
#endif
    if (!succeed) {
    #if _DEBUG
        MY_ASSERTION(false, "ウィンドウの生成に失敗しました。");
    #else 
        MessageBox(nullptr, TEXT("ウィンドウの作成に失敗しました。"), TEXT("エラー"), MB_ICONINFORMATION);
        exit(-1);
    #endif
        return;
    }
    ShowWindow(mHWnd, SW_SHOW);
}

Window::~Window() { }

void Window::setWindowSizeAndPosition(const Vec2& clientSize, const Vec2& position) {
    const Vec2 clientWindowSize = convertWindowSize(mHWnd, clientSize);
    SetWindowPos(mHWnd, nullptr,
        (int)(position.x), (int)(position.y),
        (int)(clientWindowSize.x), (int)(clientWindowSize.y),
        SWP_NOZORDER);
    mClientSize = clientSize;
}

void Window::quit() {
    PostMessage(mHWnd, WM_CLOSE, 0, 0);
}

HWND Window::getHWND() const {
    return mHWnd;
}

bool Window::isClosed() const {
    return IsWindow(mHWnd) == FALSE;
}

void Window::setProcedureEvent(IWindowProc* proc) {
    //ユニークポインタ化する
    WindowProcedures::mWindowProcs.emplace_back(std::unique_ptr<IWindowProc>(proc));
}

bool Window::isActive() const {
    return GetActiveWindow() == mHWnd;
}

void Window::setActive(bool activeFlag) {
    if (activeFlag) {
        SetActiveWindow(mHWnd);
    }
    else {
        HWND next = GetNextWindow(mHWnd, GW_HWNDNEXT);
        //SetActiveWindow(next);
        SetForegroundWindow(next);
    }
}

} //Window 
} //Framework 