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

void Transform::lookat(const Math::Vector3& target) {
    Math::Vector3 z = (target - mPosition).getNormal();
    Math::Vector3 x = Math::Vector3::cross(Math::Vector3::UP, z).getNormal();
    Math::Vector3 y = Math::Vector3::cross(z, x).getNormal();

    Math::Matrix4x4 mat = Math::Matrix4x4(
        x.x, x.y, x.z, 0,
        y.x, y.y, y.z, 0,
        z.x, z.y, z.z, 0,
        0, 0, 0, 1
    );

    mRotation = mat.toQuaternion();
}

} //Utility 
} //Framework 
