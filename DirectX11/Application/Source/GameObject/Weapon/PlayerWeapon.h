#pragma once
#include "Source/GameObject/GameObject.h"

/**
* @class PlayerWeapon
* @brief プレイヤーの武器基底クラス
*/
class PlayerWeapon : public GameObject{
public:
    /**
    * @brief コンストラクタ
    */
    PlayerWeapon(const Framework::Utility::Transform& transform,IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    virtual ~PlayerWeapon();
    /**
    * @brief トリガーを引く
    */
    virtual void pullTrigger() = 0;
};