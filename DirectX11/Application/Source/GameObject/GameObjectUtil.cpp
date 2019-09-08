#include "GameObjectUtil.h"

using namespace Framework;

Framework::Math::Vector3 GameObjectUtil::calcurateForwordVector(const Framework::Utility::Transform& transform) {
    Math::Quaternion q(0, 0, 1, 0);
    Math::Quaternion r = Math::Quaternion::conjugate(transform.getRotate()) * q * transform.getRotate();
    Math::Vector3 v(r.x, r.y, r.z);
    v.normalize();
    return v;
}
