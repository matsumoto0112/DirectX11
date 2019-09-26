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
* @class WormholeParticle
*/
class WormholeParticle : public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    WormholeParticle();
    /**
    * @brief �f�X�g���N�^
    */
    ~WormholeParticle();
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