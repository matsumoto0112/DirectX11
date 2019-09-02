#pragma once
#include "Framework/Math/Primitive3D.h"

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
    * @param intersection 交点
    */
    static bool line_plane(const Math::Line& line, const Math::Plane& plane, Math::Vector3* intersection);

};

} //Utility 
} //Framework 