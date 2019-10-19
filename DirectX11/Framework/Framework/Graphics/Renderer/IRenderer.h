#pragma once
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Graphics/Renderer/RenderTargetView.h"
#include "Framework/Graphics/Renderer/IDrawable.h"

namespace Framework {
namespace Graphics {

/**
* @class IRenderer
* @brief �`��C���^�[�t�F�[�X
*/
class IRenderer {
public:
    /**
    * @brief �R���X�g���N�^
    * @param rtv �����_�[�^�[�Q�b�g�r���[
    * @param pipeline �`��p�C�v���C��
    */
    IRenderer(std::shared_ptr<Graphics::RenderTargetView> rtv, std::shared_ptr<Graphics::RenderState> pipeline);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IRenderer() = default;
    /**
    * @brief �`�揈���J�n
    */
    virtual void begin() = 0;
    /**
    * @brief �`�揈���I��
    */
    virtual void end() = 0;
    /**
    * @brief �`�揈��
    * @param drawable �`��Ώ�
    */
    virtual void render(IDrawable* drawable) = 0;
    /**
    * @brief �`��^�[�Q�b�g���擾����
    */
    std::shared_ptr<Graphics::RenderTargetView> getRenderTarget() const { return mRenderTarget; }
    /**
    * @brief �`��X�e�[�g���擾����
    */
    std::shared_ptr<Graphics::RenderState> getPipeline() const { return mRenderState; }
protected:
    std::shared_ptr<Graphics::RenderTargetView> mRenderTarget;
    std::shared_ptr<Graphics::RenderState> mRenderState;
};

} //Graphics 
} //Framework 