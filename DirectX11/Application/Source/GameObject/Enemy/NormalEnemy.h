#pragma once
#include "Source/GameObject/Enemy/Enemy.h"

/**
* @class NormalEnemy
* @brief 通常敵
*/
class NormalEnemy : public Enemy {
public:
    struct Parameter {
    public:
        Framework::Graphics::Color4 color;
        float moveSpeed;
    };
public:
    /**
    * @brief コンストラクタ
    */
    NormalEnemy(const Framework::Utility::Transform& transform, const Parameter& parameter, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~NormalEnemy();
    /**
    * @brief 更新処理
    */
    virtual void update() override;
private:
    float mMoveSpeed;
};