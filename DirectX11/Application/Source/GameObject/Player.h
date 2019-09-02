#pragma once
#include <memory>
#include "Source/GameObject/GameObject3D.h"

/**
* @class Player
* @brief discription
*/
class Player :public GameObject3D {
public:
    /**
    * @brief コンストラクタ
    */
    Player(const Framework::Utility::Transform& transform);
    /**
    * @brief デストラクタ
    */
    ~Player();
    /**
    * @brief 更新
    */
    virtual void update() override;
private:
    float mMoveSpeed;
};