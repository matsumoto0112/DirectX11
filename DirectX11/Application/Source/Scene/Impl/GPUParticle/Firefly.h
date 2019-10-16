#pragma once
#include <memory>
#include "Source/Scene/Impl/GPUParticle/GPUParticleBase.h"

/**
* @class Firefly
* @brief ��������p�[�e�B�N���e�X�g�V�[��
*/
class Firefly : public GPUParticleBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Firefly();
    /**
    * @brief �f�X�g���N�^
    */
    ~Firefly();

    virtual void load(Framework::Scene::Collecter& collecter) override;
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
        float moveTime;
        float nextRotateTime;
        float angle;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 scale;
        Framework::Graphics::Color4 color;
    };
};