#include "Source/GameObject/Item/Item.h"

using namespace Framework;

namespace {
static constexpr float ROT_ANGLE_PER_FRAME = 0.5f;
}

Item::Item(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :Collidable3DObject(transform, mediator, Define::ModelType::Item) {}

Item::~Item() {}

void Item::update() {
    Math::Quaternion rot = Math::Quaternion::createRotateAboutY(ROT_ANGLE_PER_FRAME) * Math::Quaternion::createRotateAboutZ(ROT_ANGLE_PER_FRAME);
    mTransform.setRotate(mTransform.getRotate() * rot);
}

void Item::dispatch(Collidable3DObject* other) {
    other->hit(this);
}

void Item::hit(Player* other) {
    mIsAlive = false;
}

std::unique_ptr<Collider> Item::createCollider() {
    Utility::Transform colTransform(
        Math::Vector3::ZERO,
        Math::Quaternion::IDENTITY,
        Math::Vector3(1.0f, 1.0f, 1.0f));
    colTransform.setParent(&mTransform);

    return std::make_unique<Collider>(colTransform, this);
}
