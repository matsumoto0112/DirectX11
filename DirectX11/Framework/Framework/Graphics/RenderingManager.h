#pragma once
#include <memory>
#include "Framework/Math/Vector2.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/GraphicsDevice.h"
#include "Framework/Graphics/Light/LightManager.h"

namespace Framework {
namespace ImGUI {
class Manager;
} //ImGUI 
namespace Graphics {
class AlphaBlend;
class RenderTarget;
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
    /**
    * @brief �`��J�n
    */
    void drawBegin(const Color4& clearColor);
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
    * @brief ���C�g�Ǘ��҂̎擾
    */
    LightManager* getLightManager() const { return mLightManager.get(); }
    /**
    * @brief ImGUI�Ǘ��҂̎擾
    */
    ImGUI::Manager* getImGUIManager() const { return mImGUIManager.get(); }
private:
    Math::Vector2 mScreenSize;
    std::unique_ptr<GraphicsDevice> mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    std::unique_ptr<ConstantBufferManager> mConstantBufferManager; //!< �R���X�^���g�o�b�t�@�Ǘ�
    std::unique_ptr<LightManager> mLightManager; //!< ���C�g�Ǘ�
    std::unique_ptr<AlphaBlend> mAlphaBlend; //!< �A���t�@�u�����h
    std::unique_ptr<RenderTarget> mRenderTarget; //!< �����_�[�^�[�Q�b�g
    std::unique_ptr<Sampler> mDefaultSampler; //!< �T���v���[
    std::unique_ptr<ImGUI::Manager> mImGUIManager; //!< ImGUI�̊Ǘ�
};

} //Graphics 
} //Framework 