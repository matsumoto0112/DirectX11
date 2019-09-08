#pragma once
#include "Framework/Math/Vector3.h"
#include "Framework/Utility/Transform.h"

/**
* @class GameObjectUtil
* @brief ゲームオブジェクトユーティリティクラス
*/
class GameObjectUtil {
public:
    /**
    * @brief オブジェクトの向きから前方に向かうベクトルを取得する
    */
    static Framework::Math::Vector3 calcurateForwordVector(const Framework::Utility::Transform& transform);
};
