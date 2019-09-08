#pragma once
#include "Framework/Math/Vector3.h"
#include "Framework/Utility/Transform.h"

/**
* @class GameObjectUtil
* @brief �Q�[���I�u�W�F�N�g���[�e�B���e�B�N���X
*/
class GameObjectUtil {
public:
    /**
    * @brief �I�u�W�F�N�g�̌�������O���Ɍ������x�N�g�����擾����
    */
    static Framework::Math::Vector3 calcurateForwordVector(const Framework::Utility::Transform& transform);
};
