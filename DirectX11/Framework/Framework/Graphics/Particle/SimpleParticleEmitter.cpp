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
    //発生しているパーティクルを更新する
    for (auto&& particle : mParticles) {
        particle->simulate(delta);
    }

    //生存していなければ終了
    if (!mIsAlive)return;

    //残り時間がもうなければ終了する
    mRemainingTime -= delta;
    if (mRemainingTime < 0) {
        mIsAlive = false;
    }

    //粒子発生タイミングになったら発生させる
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
