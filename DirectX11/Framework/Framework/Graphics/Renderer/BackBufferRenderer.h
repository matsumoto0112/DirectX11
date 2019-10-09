#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class RenderTarget;

/**
* @class BackBufferRenderer
* @brief �o�b�N�o�b�t�@�Ɍ����ĕ`�悷��f�o�C�X
*/
class BackBufferRenderer : public IRenderer {
public:
    /**
    * @brief �R���X�g���N�^
    */
    BackBufferRenderer();
    /**
    * @brief �f�X�g���N�^
    */
    ~BackBufferRenderer();
    /**
    * @brief �`��J�n
    */
    virtual void begin() override;
    /**
    * @brief �`��I��
    */
    virtual void end() override;
    /**
    * @brief �X�v���C�g��`�悷��
    * @param sprite �`�悷��X�v���C�g
    */
    virtual void render(std::shared_ptr<Sprite2D> sprite) override;
    /**
    * @brief �X�v���C�g��`�悷��
    * @param sprite �`�悷��X�v���C�g
    */
    virtual void render(std::shared_ptr<Sprite3D> sprite) override;
    ///**
    //* @brief ���f����`�悷��
    //* @param model �`�悷�郂�f��
    //* @param transform �`�悷�郂�f���̃g�����X�t�H�[��
    //*/
    //virtual void render(std::shared_ptr<Model> model, const Utility::Transform& transform) override;
    /**
    * @brief �`�悵���^�[�Q�b�g�̃e�N�X�`�����擾����
    * @details �o�b�N�o�b�t�@�̃e�N�X�`���͎擾�ł��Ȃ��̂ŃG���[�ƂȂ�
    */
    virtual std::shared_ptr<Texture> getRenderedTexture() const override;
    /**
    * @brief �����_�[�^�[�Q�b�g���擾����
    */
    RenderTarget* getRenderTarget() const { return mRenderTarget.get(); }
private:
    std::unique_ptr<RenderTarget> mRenderTarget; //!< �����_�[�^�[�Q�b�g
};

} //Graphics 
} //Framework 