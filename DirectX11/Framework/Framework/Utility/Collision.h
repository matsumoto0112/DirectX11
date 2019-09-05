#pragma once
#include "Framework/Math/3DPrimitive/OBB3D.h"
#include "Framework/Math/3DPrimitive/Primitive3D.h"

namespace Framework {
namespace Utility {

/**
* @class Collision
* @brief Õ“Ë”»’è
*/
class Collision {
public:
    /**
    * @brief ü•ª‚Æ•½–Ê‚Ì”»’è
    * @param line ü•ª
    * @param plane •½–Ê
    * @param [out] intersection Œğ“_
    */
    static bool line_plane(const Math::Line& line, const Math::Plane& plane, Math::Vector3* intersection);
    /**
    * @brief OBB‚Æ•½–Ê‚ÌÕ“Ë”»’è
    * @param obb OBB
    * @param plane •½–Ê
    * @param [out] len ‚ß‚è‚İ‹——£
    * @return Õ“Ë‚µ‚Ä‚¢‚½‚çtrue‚ğ•Ô‚·
    */
    static bool obb_plane(const Math::OBB3D& obb, const Math::Plane& plane, float* len = nullptr);
};

} //Utility 
} //Framework 