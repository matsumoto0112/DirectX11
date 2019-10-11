#pragma once
#include <memory>
#include "Framework/Graphics/Camera/CameraManager.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/GraphicsDevice.h"
#include "Framework/Graphics/ImGUI/Manager.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class Sampler;

/**
* @class RenderingManager
* @brief �`��Ǘ�
*/
class RenderingManager {
public:
    /**
    * @brief �R���X�g���N�^
    * @param hWnd �E�B���h�E�n���h��
    * @param width �E�B���h�E��
    * @param height �E�B���h�E����
    * @param isFullScreen �t���X�N���[���N����
    */
    RenderingManager(HWND hWnd, UINT width, UINT height, bool isFullScreen);
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderingManager();
    /**
    * @brief ����������
    * @details �f�o�C�X���������ɏ��������������Ȃ��Ƃ����Ȃ��̂ŕʂŌĂ�
    */
    void initialize();
    /**
    * @brief �`��J�n
    * @return �o�b�N�o�b�t�@�̕`��f�o�C�X
    * @details �`�掞�͂��̃����_���[��ʂ��Əo�͂����
    */
    IRenderer* drawBegin();
    /**
    * @brief �`��I��
    */
    void drawEnd();
    /**
    * @brief �O���t�B�b�N�f�o�C�X�̎擾
    */
    GraphicsDevice* getGraphicsDevice() const { return mGraphicsDevice.get(); }
    /**
    * @brief �R���X�^���g�o�b�t�@�̎擾
    */
    ConstantBufferManager* getConstantBufferManager() const { return mConstantBufferManager.get(); }
    /**
    * @brief �J�����Ǘ��҂̎擾
    */
    CameraManager* getCameraManager() const { return mCameraManager.get(); }
    /**
    * @brief ImGUI�Ǘ��҂̎擾
    */
    ImGUI::Manager* getImGUIManager() const { return mImGUIManager.get(); }
private:
    UINT mWidth;
    UINT mHeight;
    std::unique_ptr<GraphicsDevice> mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    std::unique_ptr<ConstantBufferManager> mConstantBufferManager; //!< �R���X�^���g�o�b�t�@�Ǘ�
    std::unique_ptr<CameraManager> mCameraManager; //!< �J�����Ǘ���
    std::unique_ptr<BackBufferRenderer> mBackBufferRenderer;
    std::unique_ptr<Sampler> mDefaultSampler; //!< �T���v���[
    std::unique_ptr<ImGUI::Manager> mImGUIManager; //!< ImGUI�̊Ǘ�
};

} //Graphics 
} //Framework 