#include "Matrix4x3.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Math/Quaternion.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Math {

void Matrix4x3::identity() {
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    tx = 0.0f; ty = 0.0f; tz = 0.0f;
}

void Matrix4x3::zeroTranslation() {
    tx = ty = tz = 0.0f;
}

Matrix4x3& Matrix4x3::setTranslation(const Vector3& d) {
    tx = d.x; ty = d.y; tz = d.z;
    return *this;
}

Matrix4x3& Matrix4x3::setupTranslation(const Vector3& d) {
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    tx = d.x; ty = d.y; tz = d.z;
    return *this;
}

Matrix4x3& Matrix4x3::setupRotateX(float degree) {
    float cos = MathUtility::cos(degree);
    float sin = MathUtility::sin(degree);
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = cos, m23 = sin;
    m31 = 0.0f; m32 = -sin; m33 = cos;
    tx = ty = tz = 0.0f;
    return *this;
}

Matrix4x3& Matrix4x3::setupRotateY(float degree) {
    float cos = MathUtility::cos(degree);
    float sin = MathUtility::sin(degree);
    m11 = cos; m12 = 0.0f; m13 = -sin;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = sin; m32 = 0.0f; m33 = cos;
    tx = ty = tz = 0.0f;
    return *this;
}

Matrix4x3& Matrix4x3::setupRotateZ(float degree) {
    float cos = MathUtility::cos(degree);
    float sin = MathUtility::sin(degree);
    m11 = cos; m12 = sin; m13 = 0.0f;
    m21 = -sin; m22 = cos; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    tx = ty = tz = 0.0f;
    return *this;
}

Matrix4x3& Matrix4x3::setupRotate(const Vector3& axis, float degree) {
    MY_ASSERTION(axis.length() - 1.0f < EPSILON, "axisが単位ベクトルではありません。");
    float cos = MathUtility::cos(degree);
    float sin = MathUtility::sin(degree);

    //副次式の計算
    float a = 1.0f - cos;
    float ax = a * axis.x;
    float ay = a * axis.y;
    float az = a * axis.z;

    m11 = ax * axis.x + cos;
    m12 = ax * axis.y + axis.z * sin;
    m13 = ax * axis.z - axis.y * sin;

    m21 = ay * axis.x - axis.z * sin;
    m22 = ay * axis.y + cos;
    m23 = ay * axis.z + axis.x * sin;

    m31 = az * axis.x + axis.y * sin;
    m32 = az * axis.y - axis.x * sin;
    m33 = az * axis.z + cos;

    tx = ty = tz = 0.0f;
    return *this;
}

Matrix4x3& Matrix4x3::setupRotate(const Quaternion& rotate) {
    const float x = rotate.x;
    const float y = rotate.y;
    const float z = rotate.z;
    const float w = rotate.w;
    const float twoXPow2 = 2 * x * x;
    const float twoYPow2 = 2 * y * y;
    const float twoZPow2 = 2 * z * z;
    const float twoXY = 2 * x * y;
    const float twoYZ = 2 * y * z;
    const float twoZX = 2 * z * x;
    const float twoWX = 2 * w * x;
    const float twoWY = 2 * w * y;
    const float twoWZ = 2 * w * z;
    m11 = 1 - 2 * y * y - 2 * z * z;
    m12 = 2 * x * y + 2 * w * z;
    m13 = 2 * z * x - 2 * w * y;
    m21 = 2 * x * y - 2 * w * z;
    m22 = 1 - 2 * x * x - 2 * z * z;
    m23 = 2 * y * z + 2 * w * x;
    m31 = 2 * z * x + 2 * w * y;
    m32 = 2 * y * z - 2 * w * x;
    m33 = 1 - 2 * x * x - 2 * y * y;
    tx = 0.0f;
    ty = 0.0f;
    tz = 0.0f;
    return *this;
}

Matrix4x3& Matrix4x3::setupScale(const Vector3& s) {
    m11 = s.x; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = s.y; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = s.z;

    tx = ty = tz = 0.0f;
    return *this;
}

float Matrix4x3::determinant(const Matrix4x3& m) {
    return
        m.m11 * (m.m22 * m.m33 - m.m23 * m.m32)
        + m.m12 * (m.m23 * m.m31 - m.m21 * m.m33)
        + m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
}

Matrix4x3 Matrix4x3::inverse(const Matrix4x3& m) {
    float det = determinant(m);
    MY_ASSERTION(MathUtility::abs(det) > 0.000001f, "特異行列なため逆行列が存在しません。");

    float oneOverDet = 1.0f / det;

    Matrix4x3 r;

    r.m11 = (m.m22 * m.m33 - m.m23 * m.m32) * oneOverDet;
    r.m12 = (m.m13 * m.m32 - m.m12 * m.m33) * oneOverDet;
    r.m13 = (m.m12 * m.m23 - m.m13 * m.m22) * oneOverDet;

    r.m21 = (m.m23 * m.m31 - m.m21 * m.m33) * oneOverDet;
    r.m22 = (m.m11 * m.m33 - m.m13 * m.m31) * oneOverDet;
    r.m23 = (m.m13 * m.m21 - m.m11 * m.m23) * oneOverDet;

    r.m31 = (m.m21 * m.m32 - m.m22 * m.m31) * oneOverDet;
    r.m32 = (m.m12 * m.m31 - m.m11 * m.m32) * oneOverDet;
    r.m33 = (m.m11 * m.m22 - m.m12 * m.m21) * oneOverDet;

    r.tx = -(m.tx * r.m11 + m.ty * r.m21 + m.tz * r.m31);
    r.ty = -(m.tx * r.m12 + m.ty * r.m22 + m.tz * r.m32);
    r.tz = -(m.tx * r.m13 + m.ty * r.m23 + m.tz * r.m33);

    return r;
}

Matrix4x4 Matrix4x3::convertMatrix4x4() const {
    return Matrix4x4(m11, m12, m13, 0.0f, m21, m22, m23, 0.0f, m31, m32, m33, 0.0f, tx, ty, tz, 1.0f);
}

Matrix4x3 Matrix4x3::operator*(const Matrix4x3& a) {
    Matrix4x3 r;

    r.m11 = m11 * a.m11 + m12 * a.m21 + m13 * a.m31;
    r.m12 = m11 * a.m12 + m12 * a.m22 + m13 * a.m32;
    r.m13 = m11 * a.m13 + m12 * a.m23 + m13 * a.m33;

    r.m21 = m21 * a.m11 + m22 * a.m21 + m23 * a.m31;
    r.m22 = m21 * a.m12 + m22 * a.m22 + m23 * a.m32;
    r.m23 = m21 * a.m13 + m22 * a.m23 + m23 * a.m33;

    r.m31 = m31 * a.m11 + m32 * a.m21 + m33 * a.m31;
    r.m32 = m31 * a.m12 + m32 * a.m22 + m33 * a.m32;
    r.m33 = m31 * a.m13 + m32 * a.m23 + m33 * a.m33;

    r.tx = tx * a.m11 + ty * a.m21 + tz * a.m31 + a.tx;
    r.ty = tx * a.m12 + ty * a.m22 + tz * a.m32 + a.ty;
    r.tz = tx * a.m13 + ty * a.m23 + tz * a.m33 + a.tz;

    return r;
}

Matrix4x3& Matrix4x3::operator*=(const Matrix4x3& a) {
    *this = *this * a;
    return *this;
}

Vector3 operator*(const Vector3& p, const Matrix4x3& m) {
    return Vector3(
        p.x * m.m11 + p.y * m.m21 + p.z * m.m31 + m.tx,
        p.x * m.m12 + p.y * m.m22 + p.z * m.m32 + m.ty,
        p.x * m.m13 + p.y * m.m23 + p.z * m.m33 + m.tz
    );
}

Vector3& operator*=(Vector3& p, const Matrix4x3& m) {
    p = p * m;
    return p;
}

} //Math 
} //Framework 