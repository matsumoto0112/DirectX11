#include "Bullet.h"
#include "Framework/Utility/Time.h"

using namespace Framework;

Bullet::Bullet(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :Collidable3DObject(transform, mediator, Define::ModelType::Bullet, createCollider()),
    mSpeed(1.0f) {}

Bullet::~Bullet() {}

void Bullet::update() {
    Math::Quaternion q(0, 0, 1, 0);
    Math::Quaternion r = Math::Quaternion::conjugate(mTransform.getRotate()) * q * mTransform.getRotate();
    Math::Vector3 v(r.x, r.y, r.z);
    v.normalize();
    Math::Vector3 newPos = mTransform.getPosition() + v * mSpeed * Utility::Time::getInstance().DeltaTime;
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
