#pragma once

#include "Source/GameObject/Collidable3DObject.h"

/**
* @class Enemy
* @brief �G�N���X
*/
class Enemy : public Collidable3DObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Enemy(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~Enemy();
protected:
    virtual std::unique_ptr<Collider> createCollider() override;
private:
};