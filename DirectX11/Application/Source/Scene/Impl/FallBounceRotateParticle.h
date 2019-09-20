#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class AlphaBlend;
class OrthographicCamera;
class PerspectiveCamera;
} //Graphics 
} //Framework 

/**
* @class FallBounceRotateParticle
* @brief �������Ē��˕Ԃ�p�[�e�B�N���e�X�g�V�[��
*/
class FallBounceRotateParticle : public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    FallBounceRotateParticle();
    /**
    * @brief �f�X�g���N�^
    */
    ~FallBounceRotateParticle();
    /**
    * @brief �V�[���ǂݍ��ݏ���
    */
    virtual void load(Framework::Scene::Collecter& collecter) override;
    /**
    * @brief �X�V
    */
    virtual void update() override;
    /**
    * @brief �V�[���I�������𖞂����Ă��邩
    */
    virtual bool isEndScene() const override;
    /**
    * @brief �`��
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
    /**
    * @brief �I������
    */
    virtual void end() override;
    /**
    * @brief ���̃V�[��
    */
    virtual Define::SceneType next() override;
private:
    std::unique_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< �J����
    std::unique_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< �J����
    std::unique_ptr<Framework::Graphics::AlphaBlend> mAlphaBlend;
};