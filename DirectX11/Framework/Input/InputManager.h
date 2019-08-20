#pragma once

#include <memory>
#include <vector>
#include "Input/Keyboard.h"
namespace Framework {
namespace Window {
class Window;
} //Window 

namespace Input {
class Joystick;
class Keyboard;
class Mouse;
enum class ID;

/**
* @class InputManager
* @brief ���͊Ǘ�
*/
class InputManager {
private:
    using JoystickPtr = std::unique_ptr<Input::Joystick>;
    using KeyboardPtr = std::unique_ptr<Input::Keyboard>;
    using MousePtr = std::unique_ptr<Input::Mouse>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param mainWindow ���C���E�B���h�E�i�L�[�{�[�h�A�}�E�X�̐ݒ�ɕK�v�Ȃ��߁j
    */
    InputManager(Window::Window& mainWindow);
    /**
    * @brief �f�X�g���N�^
    */
    ~InputManager();
    /**
    * @brief �R���g���[���̎擾
    * @param playerNumber �v���C���[�ԍ�
    */
    const Joystick& getController(ID playerNumber) const;
    /**
    * @brief �L�[�{�[�h�̎擾
    */
    const Keyboard& getKeyboard() const;
    /**
    * @brief �}�E�X�̎擾
    */
    const Mouse& getMouse() const;
    /**
    * @brief �}�E�X�̎擾
    */
    Mouse& getMouse();
    /**
    * @brief �X�V
    */
    void update();
private:
    std::vector<JoystickPtr> mControllers; //!< �R���g���[��
    KeyboardPtr mKeyboard; //!< �L�[�{�[�h
    MousePtr mMouse; //!< �}�E�X�|�C���^
};

} //Input
} //Framework
