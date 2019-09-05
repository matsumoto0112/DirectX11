#pragma once

#include <array>
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"

namespace Framework {
namespace Math {

/**
* @struct Sphere
* @brief ��
*/
struct Sphere {
public:
    Vector3 center; //!< ���S���W
    float radius; //!< ���a
public:
    /**
    * @brief �R���X�g���N�^
    */
    Sphere()
        :Sphere(Math::Vector3::ZERO, 1.0f) {}
    /**
    * @brief �R���X�g���N�^
    * @param center ���S���W
    * @param radius ���a
    */
    Sphere(const Vector3& center, float radius)
        :center(center), radius(radius) {}
};

/**
* @struct Ray
* @brief ���C
*/
struct Ray {
public:
    Vector3 start; //!< �n�_
    Vector3 direction; //!< �����x�N�g��
public:
    /**
    * @brief �R���X�g���N�^
    */
    Ray() :Ray(Vector3::ZERO, Vector3(0, 0, 1)) {}
    /**
    * @brief �R���X�g���N�^
    * @param start �n�_
    * @param direction �����x�N�g��
    */
    Ray(const Vector3& start, const Vector3& direction)
        :start(start), direction(direction) {}
};

/**
* @struct Line
* @param ����
*/
struct Line {
public:
    Vector3 start; //!< �n�_
    Vector3 end; //!< �I�_
public:
    /**
    * @brief �R���X�g���N�^
    * @param start �n�_
    * @param end �I�_
    */
    Line(const Vector3& start, const Vector3& end)
        :start(start), end(end) {}
};

/**
* @struct Plane
* @brief ����
*/
struct Plane {
    Vector3 p; //!< ���ʏ�̓_
    Vector3 normal; //!< �@���x�N�g��
    /**
    * @brief �R���X�g���N�^
    * @param p ���ʏ��1�_
    * @param normal �@���x�N�g��
    */
    Plane(const Math::Vector3& p, const Vector3& normal)
        :p(p), normal(normal) {}
};

} //Math 
} //Framework 
