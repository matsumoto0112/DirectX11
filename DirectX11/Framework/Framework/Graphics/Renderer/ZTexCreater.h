#pragma once
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Graphics/Shader/Effect.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {
class Model;
/**
* @class ZTexCreater
* @brief Z�l���o�͂����e�N�X�`�����쐬����
*/
class ZTexCreater : public IRenderer {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ZTexCreater(UINT width, UINT height, std::shared_ptr<Effect> effect);
    /**
    * @brief �f�X�g���N�^
    */
    ~ZTexCreater();
    /**
    * @brief �r���[�s���ݒ肷��
    */
    void setViewMatrix(const Math::Matrix4x4& view);
    /**
    * @brief �v���W�F�N�V�����s���ݒ肷��
    */
    void setProjectionMatrix(const Math::Matrix4x4& proj);
    /**
    * @brief �o�͊J�n
    */
    void begin() override;
    /**
    * @brief �o�͏I��
    */
    void end() override;
    /**
    * @brief �o�͏���
    * @param model �ΏۂƂȂ郂�f��
    * @param transform �ΏۂƂȂ郂�f���̃g�����X�t�H�[��
    */
    void render(std::shared_ptr<Model> model, const Utility::Transform& tranform) override;
    /**
    * @brief �X�v���C�g��`�悷��
    * @param sprite �`�悷��X�v���C�g
    * @details �X�v���C�g�͑ΏۊO�Ȃ̂ŕ��ʂ̕`�������
    */
    virtual void render(std::shared_ptr<Sprite2D> sprite) override;
    /**
    * @brief �X�v���C�g��`�悷��
    * @param sprite �`�悷��X�v���C�g
    * @details �X�v���C�g�͑ΏۊO�Ȃ̂ŕ��ʂ̕`�������
    */
    virtual void render(std::shared_ptr<Sprite3D> sprite) override;
private:
    std::shared_ptr<Effect> mEffect;
    std::shared_ptr<Texture> mTexture;
    std::unique_ptr<RenderTarget> mRenderTarget;
};

} //Graphics 
} //Framework 