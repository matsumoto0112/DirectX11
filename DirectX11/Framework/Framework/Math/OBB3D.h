#pragma once
#include <array>
#include "Framework/Math/Vector3.h"
namespace Framework {
namespace Math {

struct OBB3D {
public:
    Vector3 mPosition; //!< 位置
    std::array<Vector3, 3> mNormalDirect; //!< 各軸の方向ベクトル
    Vector3 mLength;
public:
    /**
    * @brief デフォルトコンストラクタ
    */
    OBB3D() :OBB3D(Vector3::ZERO, { Vector3::RIGHT,Vector3::UP,Vector3::FORWORD }, { 1.0f,1.0f,1.0f }) {}
    /**
    * @brief コンストラクタ
    * @param position 座標
    * @param normals 各軸の正規化された方向ベクトル
    * @param lengths 各軸の中心からの長さ
    */
    OBB3D(const Vector3& position, const std::array<Vector3, 3>& normal, const Vector3& length)
        :mPosition(position), mNormalDirect(normal), mLength(length) {}
    /**
    * @brief 衝突しているか
    * @param other 他のOBB
    * @return 衝突していたらtrueを返す
    */
    bool isCollide(const OBB3D& other) const;

    void setPosition(const Math::Vector3& position);
    void setNormal(int axis, const Math::Vector3& normal);
    void setLength(const Math::Vector3& length);
};

} //Math 
} //Framework 