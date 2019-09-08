#include "Bullet.h"
#include "Framework/Utility/Time.h"
#include "Source/GameObject/GameObjectUtil.h"

using namespace Framework;

Bullet::Bullet(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :Collidable3DObject(transform, mediator, Define::ModelType::Bullet),
    mSpeed(10.0f) {}

Bullet::~Bullet() {}

void Bullet::update() {
    Math::Vector3 movement = GameObjectUtil::calcurateForwordVector(mTransform) * mSpeed * Utility::Time::getInstance().deltaTime;
    Math::Vector3 newPos = mTransform.getPosition() + movement;
    mTransform.setPosition(newPos);
}

std::unique_ptr<Collider> Bullet::createCollider() {
    Utility::Transform transform(
        Math::Vector3::ZERO,
        Math::Quaternion::IDENTITY,
        Math::Vector3(0.25f, 0.25f, 0.25f));
    transform.setParent(&mTransform);
    return std::make_unique<Collider>(transform, this);
}

void Bullet::dispatch(Collidable3DObject* other) {
    other->hit(this);
}

void Bullet::hit(Enemy* other) {
    mIsAlive = false;
}
