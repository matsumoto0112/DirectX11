#include "Vector2.h"
#include "Framework/Math/Vector3.h"
namespace Framework {
namespace Math {

const Math::Vector2 Math::Vector2::ZERO = Math::Vector2(0, 0);
const Math::Vector2 Math::Vector2::LEFT = Math::Vector2(-1, 0);
const Math::Vector2 Math::Vector2::RIGHT = Math::Vector2(1, 0);
const Math::Vector2 Math::Vector2::UP= Math::Vector2(0, 1);
const Math::Vector2 Math::Vector2::DOWN = Math::Vector2(0, -1);

Vector2::Vector2(float x, float y)
    :x(x), y(y) {}

Vector2::Vector2(const Vector2& v)
    : Vector2(v.x, v.y) {}

Vector2& Vector2::operator=(const Vector2& v) {
    x = v.x; y = v.y;
    return *this;
}

bool Vector2::operator==(const Vector2 & v) const {
    return (x == v.x && y == v.y);
}

bool Vector2::operator!=(const Vector2 & v) const {
    return (x != v.x || y != v.y);
}

Vector2 Vector2::zero() {
    return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::operator+() const {
    return *this;
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& v) const {
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const {
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(float s) const {
    return Vector2(s * x, s * y);
}

Vector2 Vector2::operator/(float s) const {
    const float oneOverS = 1.0f / s;
    return Vector2(oneOverS * x, oneOverS * y);
}

Vector2 & Vector2::operator+=(const Vector2 & v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2 & Vector2::operator*=(float s) {
    x *= s;
    y *= s;
    return *this;
}

Vector2 & Vector2::operator/=(float s) {
    const float oneOverS = 1.0f / s;
    x *= oneOverS;
    y *= oneOverS;
    return *this;
}

float Vector2::lengthSq() const {
    return x * x + y * y;
}

float Vector2::length() const {
    //2æ‚ª0ˆÈã‚È‚çƒ‹[ƒg‚ð•Ô‚·
    const float lengthSquare = lengthSq();
    if (lengthSquare > 0.0f) {
        return MathUtility::sqrt(lengthSquare);
    }
    //0‚ð•Ô‚·
    return 0.0f;
}

void Vector2::normalize() {
    //2æ‚ª0ˆÈã‚È‚ç’·‚³‚ÅŠ„‚é
    const float lengthSquare = lengthSq();
    if (lengthSquare > 0.0f) {
        const float oneOverLength = 1.0f / MathUtility::sqrt(lengthSquare);
        x *= oneOverLength;
        y *= oneOverLength;
    }
}

Vector2 Vector2::getNormal() const {
    //2æ‚ª0ˆÈã‚È‚ç’·‚³‚ÅŠ„‚é
    const float lengthSquare = lengthSq();
    if (lengthSquare > 0.0f) {
        const float oneOverLength = 1.0f / MathUtility::sqrt(lengthSquare);
        return Vector2(x * oneOverLength, y * oneOverLength);
    }
    return Vector2(0.0f, 0.0f);
}

float Vector2::dot(const Vector2 & v) const {
    return x * v.x + y * v.y;
}

float Vector2::cross(const Vector2 & v) const {
    return x * v.y - y * v.x;
}

void Vector2::clamp(const Vector2 & min, const Vector2 & max) {
    x = MathUtility::clamp<float>(x, min.x, max.x);
    y = MathUtility::clamp<float>(y, min.y, max.y);
}

Vector3 Vector2::toVector3() const {
    return Vector3(x, y, 0.0f);
}

Vector2 operator*(float s, const Vector2 & v) {
    return v * s;
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "(" << v.x << "," << v.y << ")";
    return os;
}

} //Math
} //Framework 