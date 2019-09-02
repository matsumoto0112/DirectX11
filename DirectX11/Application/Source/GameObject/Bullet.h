#pragma once

#include "Source/GameObject/GameObject3D.h"

/**
* @class Bullet
* @brief discription
*/
class Bullet : public GameObject3D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Bullet(const Framework::Utility::Transform& transform);
    /**
    * @brief �f�X�g���N�^
    */
    ~Bullet();

    virtual void update() override;

private:
    float mSpeed;
};