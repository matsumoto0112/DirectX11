#include "SimpleParticleEmitter.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
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
            auto particle = mOrigin->clone();
            particle->setVelocity(Math::Vector3(Utility::Random::getInstance().range(-5.0f, 5.0f), 1.0f, 0.0f));
            mParticles.emplace_back(std::move(particle));
        }
    }
}

void SimpleParticleEmitter::draw(IRenderer* renderer) {
    for (auto&& particle : mParticles) {
        particle->draw(renderer);
    }
}

} //Graphics 
} //Framework 
