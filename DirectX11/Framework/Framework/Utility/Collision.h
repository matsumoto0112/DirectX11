#pragma once
#include "Framework/Math/Primitive3D.h"

namespace Framework {
namespace Utility {

/**
* @class Collision
* @brief �Փ˔���
*/
class Collision {
public:
    /**
    * @brief �����ƕ��ʂ̔���
    * @param line ����
    * @param plane ����
    * @param intersection ��_
    */
    static bool line_plane(const Math::Line& line, const Math::Plane& plane, Math::Vector3* intersection);

};

} //Utility 
} //Framework 