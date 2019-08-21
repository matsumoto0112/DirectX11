#include "Matrix3x3.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Math/Matrix4x4.h"
namespace Framework {
namespace Math {

Matrix3x3::Matrix3x3() {}

Matrix3x3::Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
    :m({ { {m11,m12,m13},{m21,m22,m23},{m31,m32,m33} } }) {}

Matrix3x3::Matrix3x3(std::array<std::array<float, 3>, 3> m)
    : m(m) {}

void Matrix3x3::loadIdentity() {
    //�S�v�f��0�ɂ���
    m[0].fill(0.0f);
    m[1].fill(0.0f);
    m[2].fill(0.0f);

    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
}

Matrix3x3 Matrix3x3::identity() {
    return Matrix3x3();
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& mat) {
    this->m = mat.m;
    return *this;
}

bool Matrix3x3::operator==(const Matrix3x3 & mat) const {
    return m == mat.m;
}

bool Matrix3x3::operator!=(const Matrix3x3 & mat) const {
    return m != mat.m;
}

Matrix3x3 Matrix3x3::operator+() {
    return *this;
}

Matrix3x3 Matrix3x3::operator-() {
    Matrix3x3 mat(m);
    mat *= -1;
    return mat;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& mat) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = m[i][j] + mat.m[i][j];
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3 & mat) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = m[i][j] - mat.m[i][j];
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator*(float k) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = m[i][j] * k;
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mat) {
    Matrix3x3 result;
    result.m[0][0] = m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0];
    result.m[0][1] = m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1];
    result.m[0][2] = m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2];

    result.m[1][0] = m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0];
    result.m[1][1] = m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1];
    result.m[1][2] = m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2];

    result.m[2][0] = m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0];
    result.m[2][1] = m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1];
    result.m[2][2] = m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2];

    return result;
}

Matrix3x3 Matrix3x3::operator/(float k) {
    Matrix3x3 mat = m;
    float oneOverK = 1.0f / k;
    return mat * oneOverK;
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& mat) {
    *this = *this + mat;
    return *this;
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& mat) {
    *this = *this - mat;
    return *this;
}

Matrix3x3& Matrix3x3::operator*=(float k) {
    *this = *this * k;
    return *this;
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& mat) {
    *this = *this * mat;
    return *this;
}

Matrix3x3& Matrix3x3::operator/=(float k) {
    *this = *this / k;
    return *this;
}

Matrix3x3 Matrix3x3::createTranslate(const Vector2& v) {
    return Matrix3x3
    (
        1, 0, 0,
        0, 1, 0,
        v.x, v.y, 1
    );
}

Matrix3x3 Matrix3x3::createTranslate(float x, float y) {
    return Matrix3x3
    (
        1, 0, 0,
        0, 1, 0,
        x, y, 1
    );
}

Matrix3x3& Matrix3x3::transform(const Vector2& v) {
    m[2][0] += v.x;
    m[2][1] += v.y;
    return *this;
}

Matrix3x3& Matrix3x3::transform(float x, float y) {
    m[2][0] += x;
    m[2][1] += y;
    return *this;
}

Matrix3x3 Matrix3x3::createRotate(float degree) {
    const float sin = MathUtility::sin(degree);
    const float cos = MathUtility::cos(degree);
    return Matrix3x3
    (
        cos, sin, 0,
        -sin, cos, 0,
        0, 0, 1
    );
}

Matrix3x3& Matrix3x3::rotate(float degree) {
    Matrix3x3 r(createRotate(degree));
    *this = *this * r;
    return *this;
}

Matrix3x3 Matrix3x3::createScale(float s) {
    return Matrix3x3
    (
        s, 0, 0,
        0, s, 0,
        0, 0, 1
    );
}

Matrix3x3 Matrix3x3::createScale(const Vector2& s) {
    return Matrix3x3
    (
        s.x, 0, 0,
        0, s.y, 0,
        0, 0, 1
    );
}

Matrix3x3& Matrix3x3::scale(float s) {
    Matrix3x3 mat(createScale(s));
    *this = *this * mat;
    return *this;
}

Matrix3x3& Matrix3x3::scale(const Vector2& s) {
    Matrix3x3 mat(createScale(s));
    *this = *this * mat;
    return *this;
}

Matrix4x4 Matrix3x3::toMatrix4(const Matrix3x3& mat) {
    return Matrix4x4
    (
        mat.m[0][0], mat.m[0][1], mat.m[0][2], 0.0f,
        mat.m[1][0], mat.m[1][1], mat.m[1][2], 0.0f,
        mat.m[2][0], mat.m[2][1], mat.m[2][2], 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Vector2 operator*(const Vector2& v, const Matrix3x3& mat) {
    float x = v.x * mat.m[0][0] + v.y * mat.m[1][0] + mat.m[2][0];
    float y = v.x * mat.m[0][1] + v.y * mat.m[1][1] + mat.m[2][1];
    return Vector2(x, y);
}

Vector2& operator*=(Vector2& v, const Matrix3x3& mat) {
    v = v * mat;
    return v;
}

} // Math
} //Framework 