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
* @brief 1�E�B���h�E�̊Ǘ��N���X
*/
class Window {
private:
    using Vec2 = Math::Vector2;
public:
    /**
    * @brief �R���X�g���N�^
    * @param clientSize �N���C�A���g�̈�̑傫��
    * @param position �E�B���h�E�̍��W
    * @param windowTitle �E�B���h�E�̃^�C�g��
    * @param toWindowEndApplicationQuit �E�B���h�E�I�����ɃA�v���P�[�V�������I�������邩
    */
    Window(const Vec2& clientSize, const Vec2& position,
        const std::string& windowTitle, bool toWindowEndApplicationQuit);
    /**
    * @brief �f�X�g���N�^
    */
    ~Window();
    /**
    * @brief �E�B���h�E�̑傫���ƍ��W��ݒ�
    * @param clientSize �N���C�A���g�̈�̑傫��
    * @param position ���W
    */
    void setWindowSizeAndPosition(const Vec2& clientSize, const Vec2& position);
    /**
    * @brief �E�B���h�E�̔j��
    */
    void quit();
    /**
    * @brief �E�B���h�E�n���h���̎擾
    * @return �E�B���h�E�n���h��
    */
    HWND getHWND() const;
    /**
    * @brief �E�B���h�E������ꂽ��
    */
    bool isClosed() const;
    /**
    * @brief �E�B���h�E�v���V�[�W����ǉ�
    * @param proc �ǉ�����v���V�[�W��
    */
    void setProcedureEvent(IWindowProc* proc);
    /**
    * @brief �E�B���h�E���A�N�e�B�u��Ԃ�
    */
    bool isActive() const;

    void setActive(bool activeFlag);
private:
    HWND mHWnd; //!< �E�B���h�E�n���h��
    Vec2 mClientSize; //!< �N���C�A���g�̈�̑傫��
};

} //Window 
} //Framework 