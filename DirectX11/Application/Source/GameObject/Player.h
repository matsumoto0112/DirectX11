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
    * @brief コンストラクタ
    */
    Player(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~Player();
    /**
    * @brief 更新
    */
    virtual void update() override;
protected:
    virtual std::unique_ptr<Collider> createCollider() override;
private:
    float mMoveSpeed;
};