#pragma once
#include "Source/GameObject/Enemy/Enemy.h"

/**
* @class NormalEnemy
* @brief 通常敵
*/
class NormalEnemy {
public:
    /**
    * @brief コンストラクタ
    */
    NormalEnemy(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~NormalEnemy();
private:

};