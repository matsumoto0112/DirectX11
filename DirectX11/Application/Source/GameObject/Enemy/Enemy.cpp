#include "Enemy.h"

using namespace Framework;

Enemy::Enemy(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :Collidable3DObject(transform, mediator, Define::ModelType::Enemy, createCollider()) {}

Enemy::~Enemy() {}

std::unique_ptr<Collider> Enemy::createCollider() {
    Utility::Transform transform(
        Math::Vector3(0.0f, 1.0f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(1.75f, 2.0f, 2.0f)
    );
    transform.setParent(&mTransform);
    return std::make_unique<Collider>(transform, this);
}
