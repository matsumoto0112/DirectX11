#pragma once

#include "Source/GameObject/Collidable3DObject.h"

/**
* @class Enemy
* @brief 敵クラス
*/
class Enemy : public Collidable3DObject {
public:
    /**
    * @brief コンストラクタ
    */
    Enemy(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~Enemy();
    virtual void dispatch(Collidable3DObject* other) override;
    virtual void hit(Bullet* other) override;
protected:
    virtual std::unique_ptr<Collider> createCollider() override;
private:
};