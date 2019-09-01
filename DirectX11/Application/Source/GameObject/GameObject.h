#pragma once
#include <memory>
#include "Framework/Utility/Transform.h"

/**
* @class GameObject
* @brief discription
*/
class GameObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    GameObject(const Framework::Utility::Transform& transform)
        :mTransform(transform) {};
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~GameObject() = default;
    virtual void update() {};
    virtual void draw() {};
protected:
    Framework::Utility::Transform mTransform;
};