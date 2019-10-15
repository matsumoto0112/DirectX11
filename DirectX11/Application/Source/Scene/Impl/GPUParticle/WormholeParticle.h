#pragma once
#include <memory>
#include "Source/Scene/Impl/GPUParticle/GPUParticleBase.h"

/**
* @class WormholeParticle
*/
class WormholeParticle : public GPUParticleBase {
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
    virtual void draw(Framework::Graphics::IRenderer* pipeline) override;
private:
    struct Particle {
        float lifeTime;
        float speed;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Graphics::Color4 color;
    };
};