#include "Particle.h"
#include "Framework/Graphics/Renderer/Pipeline.h"

namespace Framework {
namespace Graphics {

Particle::Particle(std::shared_ptr<Sprite3D> sprite)
    :mSprite(sprite),
    mIsAlive(true),
    mPosition(Math::Vector3::ZERO),
    mVelocity(Math::Vector3::ZERO),
    mLifeTime(1.0f) {}

Particle::~Particle() {}

void Particle::init(Particle* origin) {
    mPosition = origin->getPosition();
    mVelocity = origin->getVelocity();
    mLifeTime = origin->getLifeTime();;
    mIsAlive = true;
}

void Particle::simulate(float delta) {
    if (!mIsAlive)return;
    mPosition += mVelocity * delta;
    mLifeTime -= delta;
    if (mLifeTime < 0) {
        mIsAlive = false;
    }
}

void Particle::draw(RenderState* pipeline) {
    if (!mIsAlive)return;
    mSprite->setPosition(mPosition);
    //pipeline->render(mSprite);
}

std::unique_ptr<Particle> Particle::clone() {
    std::unique_ptr<Particle> cloneParticle = std::unique_ptr<Particle>(new Particle(*this));
    return cloneParticle;
}

} //Graphics 
} //Framework 
