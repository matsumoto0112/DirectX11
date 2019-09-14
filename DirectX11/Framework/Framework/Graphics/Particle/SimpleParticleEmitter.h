#pragma once
#include "Framework/Graphics/Particle/ParticleEmitter.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class SimpleParticleEmitter
* @brief �V���v���p�[�e�B�N������
*/
class SimpleParticleEmitter : public ParticleEmitter {
public:
    /**
    * @brief �R���X�g���N�^
    */
    SimpleParticleEmitter(std::shared_ptr<Particle> origin);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~SimpleParticleEmitter();
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
    virtual void draw(IRenderer* renderer) override;
private:
    PROPERTY(bool, mIsAlive, IsAlive); //!< �������Ă��邩
    PROPERTY(float, mDuration, Duration); //!< ��������
    PROPERTY(float, mEmitInterval, EmitInterval); //!< �����Ԋu
    PROPERTY(float, mIntervalTimer, IntervalTimer); //!< �p�[�e�B�N���^�C�}�[
    PROPERTY(int, mOnceEmitNum, OnceEmitNum); //!< ���Ŕ��������
    PROPERTY(float, mRemainingTime, RemainingTime); //!< �p�[�e�B�N���̎c�萶������
};

} //Graphics 
} //Framework 
