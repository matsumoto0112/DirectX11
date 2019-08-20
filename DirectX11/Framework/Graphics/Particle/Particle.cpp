#include "Particle.h"

namespace Framework {
namespace Graphics {

Particle::Particle(std::shared_ptr<Sprite3D> sprite)
    :mSprite(sprite),
    mIsAlive(true),
    mPosition(Math::Vector3::ZERO),
    mVelocity(Math::Vector3::ZERO),
    mLifeTime(1.0f) {}

Particle::~Particle() {}

void Particle::simulate(float delta) {
    if (!mIsAlive)return;
    mPosition += mVelocity * delta;
    mLifeTime -= delta;
    if (mLifeTime < 0) {
        mIsAlive = false;
    }
}

void Particle::draw() {
    if (!mIsAlive)return;
    mSprite->setPosition(mPosition);
    mSprite->draw();
}

std::unique_ptr<Particle> Particle::clone() {
    std::unique_ptr<Particle> cloneParticle = std::unique_ptr<Particle>(new Particle(*this));
    return cloneParticle;
}

} //Graphics 
} //Framework 
