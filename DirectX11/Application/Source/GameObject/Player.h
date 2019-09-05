#pragma once
#include <memory>
#include "Framework/Utility/Property.h"
#include "Source/GameObject/Collidable3DObject.h"

/**
* @class Player
* @brief discription
*/
class Player :public Collidable3DObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Player(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~Player();
    /**
    * @brief �X�V
    */
    virtual void update() override;

    virtual void draw() override;

    Collider* getCollider() const;
    virtual std::unique_ptr<Collider> createCollider() override;
private:
    float mMoveSpeed;
};