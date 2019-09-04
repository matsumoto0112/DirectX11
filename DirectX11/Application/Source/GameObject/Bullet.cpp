#include "Bullet.h"
#include "Framework/Utility/Time.h"

using namespace Framework;

Bullet::Bullet(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :GameObject3D(transform, mediator, Define::ModelType::Bullet),
    mSpeed(3.0f) {

}

Bullet::~Bullet() {}

void Bullet::update() {
    Math::Quaternion q(0, 0, 1, 0);
    Math::Quaternion r = Math::Quaternion::conjugate(mTransform.getRotate()) * q * mTransform.getRotate();
    Math::Vector3 v(r.x, r.y, r.z);
    v.normalize();
    Math::Vector3 newPos = mTransform.getPosition() + v * mSpeed * Utility::Time::getInstance().DeltaTime;
    mTransform.setPosition(newPos);
}
