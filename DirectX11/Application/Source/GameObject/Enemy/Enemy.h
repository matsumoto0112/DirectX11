#pragma once

#include "Source/GameObject/GameObject3D.h"

/**
* @class Enemy
* @brief �G�N���X
*/
class Enemy : public GameObject3D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Enemy(const Framework::Utility::Transform& transform);
    /**
    * @brief �f�X�g���N�^
    */
    ~Enemy();
private:

};