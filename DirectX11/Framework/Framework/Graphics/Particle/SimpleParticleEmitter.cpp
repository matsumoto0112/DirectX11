#include "SimpleParticleEmitter.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Utility/Random.h"

namespace Framework {
namespace Graphics {

SimpleParticleEmitter::SimpleParticleEmitter(std::shared_ptr<Particle> origin)
    :ParticleEmitter(origin),
    mIsAlive(true),
    mDuration(5.0f),
    mEmitInterval(1.0f),
    mIntervalTimer(mEmitInterval),
    mOnceEmitNum(10),
    mRemainingTime(mDuration) {}

SimpleParticleEmitter::~SimpleParticleEmitter() {}

void SimpleParticleEmitter::init() {
    mIsAlive = true;
    mRemainingTime = mDuration;
    mParticles.clear();
}

void SimpleParticleEmitter::simulate(float delta) {
    //�������Ă���p�[�e�B�N�����X�V����
    for (auto&& particle : mParticles) {
        particle->simulate(delta);
    }

    //�������Ă��Ȃ���ΏI��
    if (!mIsAlive)return;

    //�c�莞�Ԃ������Ȃ���ΏI������
    mRemainingTime -= delta;
    if (mRemainingTime < 0) {
        mIsAlive = false;
    }

    //���q�����^�C�~���O�ɂȂ����甭��������
    mIntervalTimer -= delta;
    if (mIntervalTimer < 0) {
        mIntervalTimer = mEmitInterval;
        for (int i = 0; i < mOnceEmitNum; i++) {
            mParticles.emplace_back(std::move(mOrigin->clone()));
        }
    }
}

void SimpleParticleEmitter::draw(Pipeline* pipeline) {
    for (auto&& particle : mParticles) {
        particle->draw(pipeline);
    }
}

} //Graphics 
} //Framework 
