#pragma once

#include "Source/GameObject/GameObject3D.h"

/**
* @class Enemy
* @brief 敵クラス
*/
class Enemy : public GameObject3D {
public:
    /**
    * @brief コンストラクタ
    */
    Enemy(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~Enemy();
private:

};