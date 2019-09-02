#pragma once

#include "Source/GameObject/GameObject3D.h"

/**
* @class Bullet
* @brief discription
*/
class Bullet : public GameObject3D {
public:
    /**
    * @brief コンストラクタ
    */
    Bullet(const Framework::Utility::Transform& transform);
    /**
    * @brief デストラクタ
    */
    ~Bullet();

    virtual void update() override;

private:
    float mSpeed;
};