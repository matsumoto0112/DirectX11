#pragma once
#include "Framework/Graphics/Particle/ParticleEmitter.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class SimpleParticleEmitter
* @brief discription
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
    virtual void simulate(float delta) override;
    virtual void draw() override;
private:
    PROPERTY(bool, mIsAlive, IsAlive);
    float mDuration;
    float mEmitInterval;
    float mIntervalTimer;
    int mOnceEmitNum;

    float mTime;
};

} //Graphics 
} //Framework 
