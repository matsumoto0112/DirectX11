#pragma once

#include "Source/GameObject/Weapon/PlayerWeapon.h"

/**
* @class SingleShotWeapon
* @brief 単発武器
*/
class SingleShotWeapon : public PlayerWeapon {
public:
    /**
    * @brief コンストラクタ
    */
    SingleShotWeapon(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    virtual ~SingleShotWeapon();

    virtual void pullTrigger() override;
private:
    int mCounter;
};