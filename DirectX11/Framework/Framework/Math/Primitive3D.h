#pragma once

#include <array>
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"

namespace Framework {
namespace Math {

/**
* @struct Sphere
* @brief 球
*/
struct Sphere {
public:
    Vector3 center; //!< 中心座標
    float radius; //!< 半径
public:
    /**
    * @brief コンストラクタ
    */
    Sphere()
        :Sphere(Math::Vector3::ZERO, 1.0f) {}
    /**
    * @brief コンストラクタ
    * @param center 中心座標
    * @param radius 半径
    */
    Sphere(const Vector3& center, float radius)
        :center(center), radius(radius) {}
};

/**
* @struct Ray
* @brief レイ
*/
struct Ray {
public:
    Vector3 start; //!< 始点
    Vector3 direction; //!< 方向ベクトル
public:
    /**
    * @brief コンストラクタ
    */
    Ray() :Ray(Vector3::ZERO, Vector3(0, 0, 1)) {}
    /**
    * @brief コンストラクタ
    * @param start 始点
    * @param direction 方向ベクトル
    */
    Ray(const Vector3& start, const Vector3& direction)
        :start(start), direction(direction) {}
};

/**
* @struct Line
* @param 線分
*/
struct Line {
public:
    Vector3 start; //!< 始点
    Vector3 end; //!< 終点
public:
    /**
    * @brief コンストラクタ
    * @param start 始点
    * @param end 終点
    */
    Line(const Vector3& start, const Vector3& end)
        :start(start), end(end) {}
};

/**
* @struct Plane
* @brief 平面
*/
struct Plane {
    Vector3 p; //!< 平面上の点
    Vector3 normal; //!< 法線ベクトル
    /**
    * @brief コンストラクタ
    * @param p 平面上の1点
    * @param normal 法線ベクトル
    */
    Plane(const Math::Vector3& p, const Vector3& normal)
        :p(p), normal(normal) {}
};

} //Math 
} //Framework 
