#pragma once
#include "Source/GameObject/Enemy/Enemy.h"

/**
* @class NormalEnemy
* @brief �ʏ�G
*/
class NormalEnemy {
public:
    /**
    * @brief �R���X�g���N�^
    */
    NormalEnemy(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~NormalEnemy();
private:

};