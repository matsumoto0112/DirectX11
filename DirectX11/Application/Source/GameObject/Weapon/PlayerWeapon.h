#pragma once
#include "Source/GameObject/GameObject.h"

/**
* @class PlayerWeapon
* @brief �v���C���[�̕�����N���X
*/
class PlayerWeapon : public GameObject{
public:
    /**
    * @brief �R���X�g���N�^
    */
    PlayerWeapon(const Framework::Utility::Transform& transform,IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~PlayerWeapon();
    /**
    * @brief �g���K�[������
    */
    virtual void pullTrigger() = 0;
};