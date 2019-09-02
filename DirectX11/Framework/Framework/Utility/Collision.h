#pragma once
#include "Framework/Math/Primitive3D.h"

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
    * @param intersection Œğ“_
    */
    static bool line_plane(const Math::Line& line, const Math::Plane& plane, Math::Vector3* intersection);

};

} //Utility 
} //Framework 