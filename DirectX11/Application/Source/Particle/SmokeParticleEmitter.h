#pragma once
#include "Framework/Graphics/Particle/ParticleEmitter.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/Range.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Transform.h"

/**
* @class SmokeParticleEmitter
* @brief ���̃p�[�e�B�N���̃G�~�b�^�[
*/
class SmokeParticleEmitter : public Framework::Graphics::ParticleEmitter {
public:
    /**
    * @brief �R���X�g���N�^
    */
    SmokeParticleEmitter(std::shared_ptr<Framework::Graphics::Particle> particle);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~SmokeParticleEmitter();
    /**
    * @brief ����������
    */
    virtual void init() override;
    /**
    * @brief �V�~�����[�g����
    */
    virtual void simulate(float delta) override;
    /**
    * @brief �`��
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
private:
    virtual void emit(int num);
private:
    PROPERTY_GETREF(Framework::Utility::Transform, mTransform, Transform);
    PROPERTY_GETREF(Framework::Utility::Timer, mLimitTime, LimitTimer);
    PROPERTY_GETREF(Framework::Utility::Timer, mEmitTimer, EmitTimer);
    PROPERTY_GETREF(Framework::Utility::Range<Framework::Math::Vector3>, mVelocity, VelocityRange);
    PROPERTY(int, mOnceEmitNum, OnceEmitNum);
    PROPERTY(int, mMaxParticleNum, MaxParticleNum);
};