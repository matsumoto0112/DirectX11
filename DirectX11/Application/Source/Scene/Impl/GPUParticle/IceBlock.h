#pragma once
#include <memory>
#include "Source/Scene/Impl/GPUParticle/GPUParticleBase.h"

/**
* @class IceBlock
* @brief �������Ē��˕Ԃ�p�[�e�B�N���e�X�g�V�[��
*/
class IceBlock : public GPUParticleBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    IceBlock();
    /**
    * @brief �f�X�g���N�^
    */
    ~IceBlock();
    /**
    * @brief �X�V
    */
    virtual void update() override;
    /**
    * @brief �`��
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
private:
    struct Particle {
        float lifeTime;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Math::Vector3 scale;
        Framework::Math::Vector3 rotate;
        Framework::Math::Vector3 angular;
        Framework::Graphics::Color4 color;
    };

    struct CPUParameter {
        int MAX_RUNNING_PARTICLE_NUM;
        int mCurrentRunningNum;
    } mCPUParameter;

    struct GPUParameter {
        Framework::Math::Vector3 center;
        float padding[1];
    } mGPUParameter;

    std::unique_ptr<Framework::Graphics::ConstantBuffer<GPUParameter>> mEmitParameter;
};