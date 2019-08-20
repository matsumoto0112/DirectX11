#pragma once
#include <unordered_map>
#include <Windows.h>
#include "Input/KeyCode.h"
#include "Math/Vector2.h"

namespace Framework {
namespace Window {
class Window;
} //Window 

namespace Input {
class Keyboard;

/**
* @enum MouseButton
* @brief �}�E�X�̃{�^����`
*/
enum class MouseButton {
    Left = static_cast<int>(KeyCode::LButton),
    Right = static_cast<int>(KeyCode::RButton),
    Middle = static_cast<int>(KeyCode::MButton),
};

/**
* @enum CursorMode
* @brief �}�E�X�J�[�\���̏�Ԓ�`
*/
enum class CursorMode {
    Show,
    Hide,
};

/**
* @class Mouse
* @brief �}�E�X���Ǘ��N���X
*/
class Mouse {
public:
    /**
    * @brief �R���X�g���N�^
    * @param window ���C���E�B���h�E
    * @param keyboard �L�[�{�[�h
    * @details ���͂̎擾�̓L�[�{�[�h�ƈꏏ�ɍs�����߃L�[�{�[�h���K�v
    */
    Mouse(Window::Window& window, Keyboard& keyboard);
    /**
    * @brief �f�X�g���N�^
    */
    ~Mouse();
    /**
    * @brief �X�V
    */
    void update();
    /**
    * @brief �}�E�X�̍��W���擾
    * @return �N���C�A���g�̈�ł̃}�E�X���W��Ԃ�
    */
    const Math::Vector2& getMousePosition() const;
    /**
    * @brief �}�E�X�̃{�^���������Ă��邩
    * @param button �{�^���̎��
    * @return �����Ă����ԂȂ�true��Ԃ�
    */
    bool getMouse(MouseButton button) const;
    /**
    * @brief �}�E�X�̃{�^������������
    * @param button �{�^���̎��
    * @return �������^�C�~���O�Ȃ�true��Ԃ�
    */
    bool getMouseDown(MouseButton button) const;
    /**
    * @brief �}�E�X�̃{�^���𗣂�����
    * @param button �{�^���̎��
    * @return �������^�C�~���O�Ȃ�true��Ԃ�
    */
    bool getMouseUp(MouseButton button) const;
    /**
    * @brief �}�E�X�̈ړ��ʂ��擾
    */
    Math::Vector2 getMove() const;

    void setFixedPosition(const Math::Vector2& position);
    const Math::Vector2& getFixedPosition() const { return mFixedPosition; }
    void setCursorMode(CursorMode mode);
    CursorMode getCursorMode() const { return mMode; }
private:
    Window::Window& mMainWindow;
    Keyboard& mKeyboard; //!< �L�[�{�[�h
    Math::Vector2 mPosition; //!< ���̃}�E�X�̍��W
    Math::Vector2 mPrevPosition; //!< �O�̃}�E�X�̍��W
    Math::Vector2 mFixedPosition; //!< �}�E�X���Œ肷����W
    CursorMode mMode;
};

} //Input 
} //Framework
