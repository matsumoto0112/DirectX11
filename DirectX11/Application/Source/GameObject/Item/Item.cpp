#include "Source/GameObject/Item/Item.h"

using namespace Framework;

Item::Item(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :Collidable3DObject(transform, mediator, Define::ModelType::Item) {}

Item::~Item() {}

void Item::dispatch(Collidable3DObject* other) {
    other->hit(this);
}

std::unique_ptr<Collider> Item::createCollider() {
    Utility::Transform colTransform(
        Math::Vector3::ZERO,
        Math::Quaternion::IDENTITY,
        Math::Vector3(1.0f, 1.0f, 1.0f));
    return std::make_unique<Collider>(colTransform, this);
}
