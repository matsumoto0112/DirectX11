#pragma once

#include "Source/GameObject/Weapon/PlayerWeapon.h"

/**
* @class SingleShotWeapon
* @brief �P������
*/
class SingleShotWeapon : public PlayerWeapon {
public:
    /**
    * @brief �R���X�g���N�^
    */
    SingleShotWeapon(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~SingleShotWeapon();

    virtual void pullTrigger() override;
private:
    int mCounter;
};