#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class TextureString;
class SimpleParticleEmitter;
} //Graphics 
} //Framework 

/**
* @class ParticleTest
* @brief �p�[�e�B�N���e�X�g�V�[��
*/
class ParticleTest :public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ParticleTest();
    /**
    * @brief �f�X�g���N�^
    */
    ~ParticleTest();
    /**
    * @brief �V�[���f�[�^�̓ǂݍ���
    */
    virtual void load(Framework::Scene::Collecter& collecter) override;
    /**
    * @brief �X�V
    */
    virtual void update(float delta) override;
    /**
    * @brief �I�����Ă��邩
    */
    virtual bool isEndScene() const override;
    /**
    * @brief �`��
    */
    virtual void draw() override;
    /**
    * @brief �I������
    */
    virtual void end() override;
    /**
    * @brief ���̃V�[��
    */
    virtual Define::SceneType next() override;
private:
    std::unique_ptr<Framework::Graphics::TextureString> mParticleStr;
    std::unique_ptr<Framework::Graphics::SimpleParticleEmitter> mParticle;
};
