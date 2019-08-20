#pragma once
#include <memory>
#include "Math/Vector2.h"
#include "Graphics/GraphicsDevice.h"
#include "Graphics/ConstantBuffer/ConstantBufferManager.h"

namespace Framework {
namespace ImGUI {
class Manager;
} //ImGUI 
namespace Graphics {
/**
* @class RenderingManager
* @brief �`��Ǘ�
*/
class RenderingManager {
public:
    /**
    * @brief �R���X�g���N�^
    * @param hWnd �E�B���h�E�n���h��
    * @param screenSize �X�N���[���̑傫��
    * @param isFullScreen �t���X�N���[���@����
    */
    RenderingManager(HWND hWnd, const Math::Vector2& screenSize, bool isFullScreen);
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderingManager();
    /**
    * @brief ����������
    * @details �f�o�C�X���������ɏ��������������Ȃ��Ƃ����Ȃ��̂ŕʂŌĂ�
    */
    void initialize();
    void drawBegin();
    void drawEnd();
    GraphicsDevice* getGraphicsDevice() const { return mGraphicsDevice.get(); }
    ConstantBufferManager* getConstantBufferManager() const { return mConstantBufferManager.get(); }
    ImGUI::Manager* getImGUIManager() const { return mImGUIManager.get(); }
private:
    Math::Vector2 mScreenSize;
    std::unique_ptr<GraphicsDevice> mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    std::unique_ptr<ConstantBufferManager> mConstantBufferManager; //!< �R���X�^���g�o�b�t�@�Ǘ�
    std::unique_ptr<ImGUI::Manager> mImGUIManager; //!< ImGUI�̊Ǘ�
};

} //Graphics 
} //Framework 