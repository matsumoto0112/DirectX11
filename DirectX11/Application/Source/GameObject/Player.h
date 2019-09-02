#pragma once
#include <memory>
#include "Source/GameObject/GameObject3D.h"

class IMainSceneMediator;

/**
* @class Player
* @brief discription
*/
class Player :public GameObject3D {
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
private:
    IMainSceneMediator& mMediator;
    float mMoveSpeed;
};