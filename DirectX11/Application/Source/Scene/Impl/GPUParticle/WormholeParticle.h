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
    * @brief �`��
    */
    virtual void draw(Framework::Graphics::IRenderer* pipeline) override;
private:
    /**
    * @brief �p�[�e�B�N���\����
    */
    struct Particle {
        float lifeTime;
        float speed;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Graphics::Color4 color;
    };
    /**
    * @brief GPU�ŗ��p����p�[�e�B�N���̃G�~�b�g�p�����[�^
    */
    struct ParticleGPUParameter {
        UINT index;
        Framework::Math::Vector3 spot;
        Framework::Math::Vector3 center;
        float radius;
    };
    /**
    * @brief CPU�ŗ��p����p�[�e�B�N���̃G�~�b�g�p�����[�^
    */
    struct ParticleCPUParameter {
        UINT MAX_RUNS_GPUPARTICLE_NUM; //!< �ő�ŗ��p����p�[�e�B�N���̎��s��
        int mCurrentRunsGPUParticleNum; //!< ���݂̃p�[�e�B�N�����s��
        float mSpeed; //!< �p�[�e�B�N���̐����n�_�̈ړ����x
        float mMaxYPosition; //!< �ő�Y���W�l
    };
    std::unique_ptr<Framework::Graphics::ConstantBuffer<ParticleGPUParameter>> mParameterCB; //<! �p�����[�^�p�R���X�^���g�o�b�t�@
    ParticleGPUParameter mGPUParameter;
    ParticleCPUParameter mCPUParameter;
};