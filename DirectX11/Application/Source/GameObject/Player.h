#pragma once
#include <memory>
#include "Framework/Utility/Property.h"
#include "Source/GameObject/GameObject3D.h"

namespace Framework {
namespace Graphics {
class Cube;
} //Graphics 
} //Framework 

class IMainSceneMediator;
class Collider;

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

    virtual void draw() override;

    Collider* getCollider() const { return mCollider.get(); }
private:
    IMainSceneMediator& mMediator;
    float mMoveSpeed;
    std::unique_ptr<Collider> mCollider;
};