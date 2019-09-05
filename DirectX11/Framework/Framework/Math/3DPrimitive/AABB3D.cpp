#include "AABB3D.h"

namespace Framework {
namespace Math {
AABB3D::AABB3D()
    :AABB3D(Vector3::ZERO, Vector3::ZERO) {}

AABB3D::AABB3D(const Vector3& min, const Vector3& max)
    : mMin(min), mMax(max) {}

AABB3D::~AABB3D() {}

void AABB3D::add(const Vector3& p) {
    if (p.x < mMin.x)mMin.x = p.x;
    if (p.x > mMax.x)mMax.x = p.x;
    if (p.y < mMin.y)mMin.y = p.y;
    if (p.y > mMax.y)mMax.y = p.y;
    if (p.z < mMin.z)mMin.z = p.z;
    if (p.z > mMax.z)mMax.z = p.z;
}

void AABB3D::setToTransformedAABB(const AABB3D& box, const Matrix4x4& m) {
    mMin = mMax = m.getTranslate();
    if (m.m[0][0] > 0.0f) {
        mMin.x += m.m[0][0] * box.mMin.x; mMax.x += m.m[0][0] * box.mMax.x;
    }
    else {
        mMin.x += m.m[0][0] * box.mMax.x; mMax.x += m.m[0][0] * box.mMin.x;
    }
    if (m.m[0][1] > 0.0f) {
        mMin.y += m.m[0][1] * box.mMin.x; mMax.y += m.m[0][1] * box.mMax.x;
    }
    else {
        mMin.y += m.m[0][1] * box.mMax.x; mMax.y += m.m[0][1] * box.mMin.x;
    }
    if (m.m[0][2] > 0.0f) {
        mMin.z += m.m[0][2] * box.mMin.x; mMax.z += m.m[0][2] * box.mMax.x;
    }
    else {
        mMin.z += m.m[0][2] * box.mMax.x; mMax.z += m.m[0][2] * box.mMin.x;
    }
    if (m.m[1][0] > 0.0f) {
        mMin.x += m.m[1][0] * box.mMin.y; mMax.x += m.m[1][0] * box.mMax.y;
    }
    else {
        mMin.x += m.m[1][0] * box.mMax.y; mMax.x += m.m[1][0] * box.mMin.y;
    }
    if (m.m[1][1] > 0.0f) {
        mMin.y += m.m[1][1] * box.mMin.y; mMax.y += m.m[1][1] * box.mMax.y;
    }
    else {
        mMin.y += m.m[1][1] * box.mMax.y; mMax.y += m.m[1][1] * box.mMin.y;
    }
    if (m.m[1][2] > 0.0f) {
        mMin.z += m.m[1][2] * box.mMin.y; mMax.z += m.m[1][2] * box.mMax.y;
    }
    else {
        mMin.z += m.m[1][2] * box.mMax.y; mMax.z += m.m[1][2] * box.mMin.y;
    }
    if (m.m[2][0] > 0.0f) {
        mMin.x += m.m[2][0] * box.mMin.z; mMax.x += m.m[2][0] * box.mMax.z;
    }
    else {
        mMin.x += m.m[2][0] * box.mMax.z; mMax.x += m.m[2][0] * box.mMin.z;
    }
    if (m.m[2][1] > 0.0f) {
        mMin.y += m.m[2][1] * box.mMin.z; mMax.y += m.m[2][1] * box.mMax.z;
    }
    else {
        mMin.y += m.m[2][1] * box.mMax.z; mMax.y += m.m[2][1] * box.mMin.z;
    }
    if (m.m[2][2] > 0.0f) {
        mMin.z += m.m[2][2] * box.mMin.z; mMax.z += m.m[2][2] * box.mMax.z;
    }
    else {
        mMin.z += m.m[2][2] * box.mMax.z; mMax.z += m.m[2][2] * box.mMin.z;
    }
}

bool AABB3D::contains(const Vector3& p) const {
    return
        (mMin.x <= p.x && p.x <= mMax.x) &&
        (mMin.y <= p.y && p.y <= mMax.y) &&
        (mMin.z <= p.z && p.z <= mMax.z);
}

bool AABB3D::intersect(const AABB3D& box1, const AABB3D& box2) {
    if (box1.mMin.x > box2.mMax.x)return false;
    if (box1.mMax.x < box2.mMin.x)return false;
    if (box1.mMin.y > box2.mMax.y)return false;
    if (box1.mMax.y < box2.mMin.y)return false;
    if (box1.mMin.z > box2.mMax.z)return false;
    if (box1.mMax.z < box2.mMin.z)return false;
    return true;
}

} //Math 
} //Framework 
