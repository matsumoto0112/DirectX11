#pragma once
#include <memory>
#include "Source/Scene/Impl/GPUParticle/GPUParticleBase.h"

/**
* @class FallParticle
* @brief ��������p�[�e�B�N���e�X�g�V�[��
*/
class FallParticle : public GPUParticleBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    FallParticle();
    /**
    * @brief �f�X�g���N�^
    */
    ~FallParticle();
    /**
    * @brief �X�V
    */
    virtual void update() override;
    /**
    * @brief �`��
    */
    virtual void draw(Framework::Graphics::IRenderer* pipeline) override;
private:
    struct Particle {
        float lifeTime;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Graphics::Color4 color;
    };
};