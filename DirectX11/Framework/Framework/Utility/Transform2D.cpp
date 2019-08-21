#include "Transform2D.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Math/Matrix4x3.h"

namespace Framework {
namespace Utility {

Transform2D::Transform2D(const Math::Vector2& position, const Math::Vector2& scale, float rotate)
    :mPosition(position), mScale(scale), mRotate(rotate), mParent(nullptr) {}

Transform2D::~Transform2D() {}

void Transform2D::setPosition(const Math::Vector2& position) {
    mPosition = position;
}

const Math::Vector2& Transform2D::getPosition() const {
    return mPosition;
}

void Transform2D::setScale(const Math::Vector2& scale) {
    mScale = scale;
}

const Math::Vector2& Transform2D::getScale() const {
    return mScale;
}

void Transform2D::setRotate(float rotate) {
    mRotate = rotate;
}

float Transform2D::getRotate() const {
    return mRotate;
}

Math::Matrix4x4 Transform2D::createSRTMatrix() const {
    if (mParent != nullptr) {
        return   createLocalSRTMatrix() * mParent->createSRTMatrix();
    }
    return createLocalSRTMatrix();
}

Math::Matrix4x4 Transform2D::createLocalSRTMatrix() const {
    Math::Matrix4x3 rotate;
    rotate.setupRotateZ(mRotate);
    Math::Matrix4x3 scale;
    scale.setupScale(mScale.toVector3());
    Math::Matrix4x3 world = (scale * rotate);
    world.setTranslation(mPosition.toVector3());
    return world.convertMatrix4x4();
}

void Transform2D::setParent(Transform2D* parent) {
    mParent = parent;
}

const Transform2D* Transform2D::getParent() const {
    return mParent;
}
} //Utility 
} //Framework 
