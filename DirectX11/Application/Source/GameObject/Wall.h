#pragma once
#include "Framework/Math/3DPrimitive/Primitive3D.h"
#include "Source/GameObject/GameObject3D.h"

class Collider;

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
    /**
    * @brief ゲームオブジェクトを壁の中に押し戻す
    */
    void pushBackGameObject(Collider& collider);
    virtual void draw() override;
private:
    Framework::Math::Plane mPlane;
};