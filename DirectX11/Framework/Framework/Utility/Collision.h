#pragma once
#include "Framework/Math/3DPrimitive/OBB3D.h"
#include "Framework/Math/3DPrimitive/Primitive3D.h"

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
    * @param [out] intersection ��_
    */
    static bool line_plane(const Math::Line& line, const Math::Plane& plane, Math::Vector3* intersection);
    /**
    * @brief OBB�ƕ��ʂ̏Փ˔���
    * @param obb OBB
    * @param plane ����
    * @param [out] len �߂荞�݋���
    * @return �Փ˂��Ă�����true��Ԃ�
    */
    static bool obb_plane(const Math::OBB3D& obb, const Math::Plane& plane, float* len = nullptr);
};

} //Utility 
} //Framework 