#include "Quaternion.h"
#include <math.h>
#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"
#include "Utility/Debug.h"
namespace Framework {
namespace Math {

Quaternion::Quaternion() {
    identity();
}

Quaternion::Quaternion(float x, float y, float z, float w)
    :x(x), y(y), z(z), w(w) {}

void Quaternion::identity() {
    w = 1.0f;
    x = y = z = 0.0f;
}

void Quaternion::setToRotateAboutX(float theta) {
    const float thetaOver2 = theta * 0.5f;
    w = cosf(thetaOver2);
    x = sinf(thetaOver2);
    y = 0.0f;
    z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta) {
    const float thetaOver2 = theta * 0.5f;
    w = cosf(thetaOver2);
    x = 0.0f;
    y = sinf(thetaOver2);
    z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta) {
    const float thetaOver2 = theta * 0.5f;
    w = cosf(thetaOver2);
    x = 0.0f;
    y = 0.0f;
    z = sinf(thetaOver2);
}
void Quaternion::setToRotateAboutAxis(const Vector3& axis, float theta) {
    MY_ASSERTION(
        fabs(axis.length() - 1.0f) < EPSILON,
        "‰ñ“]Ž²‚ª³‹K‰»‚³‚ê‚Ä‚¢‚Ü‚¹‚ñB");
    const float thetaOver2 = theta * 0.5f;
    const float sinThetaOver2 = sinf(thetaOver2);
    w = cosf(thetaOver2);
    x = sinThetaOver2 * axis.x;
    y = sinThetaOver2 * axis.y;
    z = sinThetaOver2 * axis.z;
}

Quaternion Quaternion::operator*(const Quaternion& a) const {
    Quaternion result;
    result.w = w * a.w - (x * a.x + y * a.y + z * a.z);
    result.x = w * a.x + x * a.w + z * a.y - y * a.z;
    result.y = w * a.y + y * a.w + x * a.z - z * a.x;
    result.z = w * a.z + z * a.w + y * a.x - x * a.y;
    return result;
}

Matrix4x4 Quaternion::toMatrix() const {
    const float twoXX = 2 * x * x;
    const float twoYY = 2 * y * y;
    const float twoZZ = 2 * z * z;
    const float twoXY = 2 * x * y;
    const float twoYZ = 2 * y * z;
    const float twoZX = 2 * z * x;
    const float twoWX = 2 * w * x;
    const float twoWY = 2 * w * y;
    const float twoWZ = 2 * w * z;
    return Matrix4x4
    (
        1 - twoYY - twoZZ, twoXY + twoWZ, twoZX - twoWY, 0,
        twoXY - twoWZ, 1 - twoXX - twoZZ, twoYZ + twoWX, 0,
        twoZX + twoWY, twoYZ - twoWX, 1 - twoXX - twoYY, 0,
        0, 0, 0, 1
    );
}

float Quaternion::dot(const Quaternion& a) const {
    return w * a.w + x * a.x + y * a.y + z * a.z;
}

Vector3 Quaternion::toEular() const {
    float ww = w * w;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float yy = y * y;
    float yz = y * z;
    float zz = z * z;
    Math::Vector3 result(
        MathUtility::atan2(2.0f *(yz + wx), ww - xx - yy + zz),
        MathUtility::asin(2.0f * (wy - xz)),
        MathUtility::atan2(2.0f *(xy + wz), ww + xx - yy - zz)
    );
    return result;
}

Math::Quaternion Quaternion::conjugate(const Math::Quaternion& q) {
    return Math::Quaternion(-q.x, -q.y, -q.z, q.w);
}

Math::Quaternion Quaternion::createLookTarget(const Math::Vector3& v, const Math::Vector3& normal) {
    MY_ASSERTION((v.length() - 1 <= EPSILON), "•ûŒüƒxƒNƒgƒ‹‚ð³‹K‰»‚µ‚Ä‚­‚¾‚³‚¢");
    Math::Vector3 n = Vector3::cross(normal, v);
    n.normalize();
    float angle = MathUtility::acos(Vector3::dot(v, normal));
    Math::Quaternion q;
    q.setToRotateAboutAxis(n, MathUtility::toRadian(angle));
    return q;
}

Math::Vector3 Quaternion::multiply(const Math::Vector3& v) {
    Math::Quaternion conj = Math::Quaternion::conjugate(*this);
    Math::Quaternion q(v.x, v.y, v.z, 0.0f);
    Math::Quaternion res = conj * q * *this;
    return Math::Vector3(res.x, res.y, res.z);
}

std::ostream & operator<<(std::ostream& os, const Quaternion& q) {
    os << "(" << q.x << "," << q.y << "," << q.z << "," << q.w << ")";
    return os;
}

} //Math
} //Framework 