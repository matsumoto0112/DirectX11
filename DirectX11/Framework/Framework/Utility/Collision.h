#pragma once
#include "Framework/Math/3DPrimitive/OBB3D.h"
#include "Framework/Math/3DPrimitive/Primitive3D.h"

namespace Framework {
namespace Utility {

/**
* @class Collision
* @brief 衝突判定
*/
class Collision {
public:
    /**
    * @brief 線分と平面の判定
    * @param line 線分
    * @param plane 平面
    * @param [out] intersection 交点
    */
    static bool line_plane(const Math::Line& line, const Math::Plane& plane, Math::Vector3* intersection);
    /**
    * @brief OBBと平面の衝突判定
    * @param obb OBB
    * @param plane 平面
    * @param [out] len めり込み距離
    * @return 衝突していたらtrueを返す
    */
    static bool obb_plane(const Math::OBB3D& obb, const Math::Plane& plane, float* len = nullptr);
};

} //Utility 
} //Framework 