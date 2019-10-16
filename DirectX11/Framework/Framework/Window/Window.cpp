#include "Window.h"
#include <atlstr.h>
#include "Framework/Utility/Debug.h"
#include "Framework/Window/WindowProcedures.h"

namespace {
Framework::Math::Vector2 convertWindowSize(HWND hWnd, const Framework::Math::Vector2& clientSize) {
    RECT windowRect; //�E�B���h�E�̑傫��
    RECT clientRect; //�N���C�A���g�̈�̑傫��
    GetWindowRect(hWnd, &windowRect);
    GetClientRect(hWnd, &clientRect);
    //�N���C�A���g�̈�̑傫������E�B���h�E�̑傫���ɕϊ�
    const float width = clientSize.x + (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left);
    const float height = clientSize.y + (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top);
    return Framework::Math::Vector2(width, height);
}

bool createWindow(HWND* hWnd,
    const Framework::Math::Vector2& clientSize, const Framework::Math::Vector2& position,
    const CString& name, bool toWindowEndApplicationQuit) {
    // �E�B���h�E�N���X�̃p�����[�^�ݒ�
    WNDCLASSEX wcex;
    //�\���̂̃T�C�Y
    wcex.cbSize = sizeof(WNDCLASSEX);
    //�E�B���h�E�X�^�C��
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    //�E�B���h�E�̃��b�Z�[�W����������R�[���o�b�N�֐��̓o�^
    wcex.lpfnWndProc = Framework::Window::WindowProcedures::mainWndProc;
    //�E�C���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�o�C�g��
    wcex.cbClsExtra = 0;
    //�E�C���h�E�C���X�^���X�̌��Ɋ��蓖�Ă�⑫�o�C�g��
    wcex.cbWndExtra = 0;
    //���̃N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n���h��
    wcex.hInstance = GetModuleHandle(NULL);
    //�A�C�R���̃n���h��
    wcex.hIcon = NULL;
    //�}�E�X�J�[�\���̃n���h��
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    //�E�C���h�E�w�i�F
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW - 1);
    //�f�t�H���g���j���[��
    wcex.lpszMenuName = NULL;
    //wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    //�E�C���h�E�N���X�ɂ��閼�O
    wcex.lpszClassName = name;
    //16�~16�̏������T�C�Y�̃A�C�R��
    wcex.hIconSm = NULL;
    //�o�^�Ɏ��s�����玸�s�����ƕԂ�
    if (!RegisterClassEx(&wcex))
        return false;

    //�E�B���h�E�̑傫�����擾
    const Framework::Math::Vector2 windowSize = convertWindowSize(*hWnd, clientSize);
    //�E�B���h�E�̐���    
    *hWnd = CreateWindow(name, name,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        (int)(position.x), (int)(position.y),
        (int)(windowSize.x), (int)(windowSize.y),
        nullptr, nullptr, wcex.hInstance,
        NULL);
    //�o�^�Ɏ��s�����玸�s�����ƕԂ�
    if (!(*hWnd))
        return false;

    //�E�B���h�E�̑傫���������[�X���[�h���ɈႤ���Ƃ�����̂ł����ōĎw��
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
        MY_ASSERTION(false, "�E�B���h�E�̐����Ɏ��s���܂����B");
    #else 
        MessageBox(nullptr, TEXT("�E�B���h�E�̍쐬�Ɏ��s���܂����B"), TEXT("�G���["), MB_ICONINFORMATION);
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
    //���j�[�N�|�C���^������
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