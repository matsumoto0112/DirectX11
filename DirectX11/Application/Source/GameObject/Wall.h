#pragma once
#include "Source/GameObject/GameObject3D.h"

namespace Framework {
namespace Graphics {
class Cube;
} //Graphics 
} //Framework 

class Collider;
class IMainSceneMediator;

/**
* @class Wall
* @brief 壁
*/
class Wall :public GameObject3D {
public:
    /**
    * @brief コンストラクタ
    */
    Wall(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~Wall();

    virtual void draw() override;

    Collider* getCollider() const { return mCollider.get(); }
private:
    std::unique_ptr<Collider> mCollider;
};