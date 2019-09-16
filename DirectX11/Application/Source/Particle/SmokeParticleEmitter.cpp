#include "SmokeParticleEmitter.h"
#include "Framework/Utility/Random.h"

using namespace Framework;

namespace {
Math::Vector3 getRandomVelocity(const Utility::Range<Math::Vector3>& range) {
    Utility::Random& rand = Utility::Random::getInstance();
    return Math::Vector3(
        rand.range(range.getMin().x, range.getMax().x),
        rand.range(range.getMin().y, range.getMax().y),
        rand.range(range.getMin().z, range.getMax().z)
    );
}

std::unique_ptr<Graphics::Particle> emitOnce(Graphics::Particle* origin, const Math::Vector3& vel) {
    std::unique_ptr<Graphics::Particle> res = origin->clone();
    res->setVelocity(vel);
    return std::move(res);
}
}

SmokeParticleEmitter::SmokeParticleEmitter(std::shared_ptr<Graphics::Particle> particle)
    :ParticleEmitter(particle),
    mLimitTime(5.0f),
    mEmitTimer(5.0f),
    mOnceEmitNum(0),
    mMaxParticleNum(0) {}

SmokeParticleEmitter::~SmokeParticleEmitter() {}

void SmokeParticleEmitter::init() {
    mParticles.clear();
    mLimitTime.init();
    mEmitTimer.init();
}

void SmokeParticleEmitter::simulate(float delta) {
    for (auto&& p : mParticles) {
        p->simulate(delta);
    }
    //mParticles.erase(std::remove_if(mParticles.begin(), mParticles.end(), [](auto&& p) {return !p->getIsAlive(); }), mParticles.end());

    if (mLimitTime.isTime())return;
    mLimitTime.update(delta);
    mEmitTimer.update(delta);
    if (mEmitTimer.isTime()) {
        while (mEmitTimer.isTime()) {
            mEmitTimer.setCurrentTime(mEmitTimer.getCurrentTime() + mEmitTimer.getLimitTime());
            emit(mOnceEmitNum);
        }
    }
}

void SmokeParticleEmitter::draw(Graphics::IRenderer* renderer) {
    for (auto&& particle : mParticles) {
        particle->draw(renderer);
    }
}

void SmokeParticleEmitter::emit(int num) {
    for (int i = 0; i < num; i++) {
        if (getParticleNum() >= mMaxParticleNum) {
            for (auto&& p : mParticles) {
                if (p->getIsAlive())continue;
                p->init(mOrigin.get());
                p->setVelocity(getRandomVelocity(mVelocity));
            }
        }
        else {
            mParticles.emplace_back(emitOnce(mOrigin.get(), getRandomVelocity(mVelocity)));
        }
    }
}
