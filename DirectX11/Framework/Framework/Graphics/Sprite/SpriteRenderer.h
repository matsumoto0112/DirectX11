#pragma once

#include <memory>
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Graphics {
class Effect;
class GraphicsDeviceManager;
class Sprite2D;
class Sprite3D;
class VertexAndIndexBuffer;
class Sampler;
class PerspectiveCamera;

/**
* @class SpriteRenderer
* @brief �X�v���C�g�`���
*/
class SpriteRenderer : public Utility::Singleton<SpriteRenderer> {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    */
    SpriteRenderer();
    /**
    * @brief �f�X�g���N�^
    */
    ~SpriteRenderer();
    /**
    * @brief �X�v���C�g��`�悷��
    * @param sprite �`�悷��X�v���C�g
    */
    void draw(Sprite2D* sprite);
    /**
    * @brief �X�v���C�g��Ǝ��V�F�[�_�[�ŕ`�悷��
    * @param sprite �`�悷��X�v���C�g
    * @param effect �g�p����G�t�F�N�g
    */
    void draw(Sprite2D* sprite, std::shared_ptr<Effect> effect);
    /**
    * @brief 3D�X�v���C�g���r���{�[�h�ŕ`��
    * @param sprite �`�悷��X�v���C�g
    */
    void draw(Sprite3D* sprite, const PerspectiveCamera& camera);
private:
    std::shared_ptr<VertexAndIndexBuffer> mVIBuffer; //!< ���_�E�C���f�b�N�X�o�b�t�@
    std::shared_ptr<Effect> mEffect; //!< �G�t�F�N�g
    std::unique_ptr<Sampler> mSampler; //!< �T���v���[
};

} //Graphics 
} //Framework 