#pragma once
#include <Windows.h>
#include <vector>
#include <memory>
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Window {
class Window;
} //Window 
namespace Graphics {
class RenderingManager;
} //Graphics 
namespace Input {
class InputManager;
} //Input 

namespace Device {

/**
* @class GameDevice
* @brief �Q�[���@��Ǘ�
*/
class GameDevice : public Utility::Singleton<GameDevice> {
private:
    using WindowPtr = std::unique_ptr<Window::Window>;
    using RenderingManagerPtr = std::unique_ptr<Graphics::RenderingManager>;
    using InputManagerPtr = std::unique_ptr<Input::InputManager>;
public:
    /**
    * @brief �f�o�C�X�̍X�V
    */
    void update();
    /**
    * @brief �Q�[�����I�����Ă��邩
    */
    bool isEnd() const;
    /**
    * @brief �I������
    */
    void finalize();
    /**
    * @brief ����������
    */
    void initialize(const Math::Vector2& screenSize, const std::string& title);
protected:
    /**
    * @brief �R���X�g���N�^
    * @details private�ɂ����unique_ptr���쐬�ł��Ȃ�����protected
    */
    GameDevice();
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~GameDevice();
public:
    /**
    * @brief ���C���E�B���h�E�̎擾
    */
    Window::Window* getWindow() const;
    /**
    * @brief �O���t�B�b�N�f�o�C�X�̎擾
    */
    Graphics::RenderingManager* getRenderingManager() const;
    /**
    * @brief ���͊Ǘ��f�o�C�X�̎擾
    */
    Input::InputManager* getInputManager() const;

private:
    WindowPtr mMainWindow; //!< ���C���E�B���h�E
    RenderingManagerPtr mRenderingManager; //!< �O���t�B�b�N�f�o�C�X
    InputManagerPtr mInputManager; //!< ���͊Ǘ�
};

} //Device 
} //Framework 