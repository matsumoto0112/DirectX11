#pragma once

#include "Source/GameObject/Collidable3DObject.h"

/**
* @class Bullet
* @brief discription
*/
class Bullet : public Collidable3DObject {
public:
    /**
    * @brief コンストラクタ
    */
    Bullet(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~Bullet();

    virtual void update() override;
    virtual void outOfArea();
    virtual void dispatch(Collidable3DObject* other) override;
    virtual void hit(Enemy* other) override;
protected:
    virtual std::unique_ptr<Collider> createCollider() override;
private:
    float mSpeed;
};