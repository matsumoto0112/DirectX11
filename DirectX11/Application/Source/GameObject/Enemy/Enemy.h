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
protected:
    virtual std::unique_ptr<Collider> createCollider() override;
private:
};