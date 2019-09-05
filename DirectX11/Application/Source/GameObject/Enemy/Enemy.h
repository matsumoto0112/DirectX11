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
    virtual void dispatch(Collidable3DObject* other) override;
    virtual void hit(Bullet* other) override;
protected:
    virtual std::unique_ptr<Collider> createCollider() override;
private:
};