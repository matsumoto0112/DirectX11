#include "SimpleParticleEmitter.h"

namespace Framework {
namespace Graphics {

SimpleParticleEmitter::SimpleParticleEmitter(std::shared_ptr<Particle> origin)
    :ParticleEmitter(origin),
    mIsAlive(true),
    mDuration(5.0f),
    mEmitInterval(1.0f),
    mIntervalTimer(mEmitInterval),
    mOnceEmitNum(10.0f),
    mTime(mDuration) {}

SimpleParticleEmitter::~SimpleParticleEmitter() {}

void SimpleParticleEmitter::simulate(float delta) {
    for (auto&& particle : mParticles) {
        particle->simulate(delta);
    }
    if (!mIsAlive)return;
    mTime -= delta;
    if (mTime < 0) {
        mIsAlive = false;
    }
    mIntervalTimer -= delta;
    if (mIntervalTimer < 0) {
        mIntervalTimer = mEmitInterval;
        for (int i = 0; i < mOnceEmitNum; i++) {
            mParticles.emplace_back(mOrigin->clone());
        }
    }

}

void SimpleParticleEmitter::draw() {
    for (auto&& particle : mParticles) {
        particle->draw();
    }
}

} //Graphics 
} //Framework 
