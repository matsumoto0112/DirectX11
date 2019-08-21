#include "Transform.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Math/Matrix4x3.h"

namespace Framework {
namespace Utility {

Transform::Transform()
    :Transform(Math::Vector3(0.0f, 0.0f, 0.0f),
        Math::Quaternion(),
        Math::Vector3(1.0f, 1.0f, 1.0f)) {}

Transform::Transform(const Math::Vector3& position,
    const Math::Quaternion& rotate,
    const Math::Vector3& scale)
    : mParent(nullptr), mPosition(position), mRotation(rotate), mScale(scale) {}

Transform::~Transform() {}

Math::Vector3 Transform::getGlobalPostition() const {
    if (!mParent)return mPosition;
    return  mPosition + mParent->getGlobalPostition();
}

Math::Quaternion Transform::getGlobalRotate() const {
    if (!mParent)return mRotation;
    return mRotation * mParent->getGlobalRotate();
}

Math::Vector3 Transform::getGlobalScale() const {
    if (!mParent)return mScale;
    Math::Vector3 parent = mParent->getGlobalScale();
    return Math::Vector3(mScale.x * parent.x, mScale.y * parent.y, mScale.z * parent.z);
}

Math::Matrix4x4 Transform::createSRTMatrix() const {
    if (mParent) {
        return  createLocalSRTMatrix() * mParent->createSRTMatrix();
    }
    return createLocalSRTMatrix();
}

Math::Matrix4x4 Transform::createLocalSRTMatrix() const {
    Math::Matrix4x3 scale;
    scale.setupScale(mScale);
    Math::Matrix4x3 rotate;
    rotate.setupRotate(mRotation);
    Math::Matrix4x3 world(scale * rotate);
    world.setTranslation(mPosition);
    return world.convertMatrix4x4();
}

void Transform::setParent(Transform* parent) {
    mParent = parent;
}

} //Utility 
} //Framework 
