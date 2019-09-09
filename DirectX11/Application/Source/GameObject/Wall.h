#pragma once
#include "Framework/Math/3DPrimitive/Primitive3D.h"
#include "Source/GameObject/Collidable3DObject.h"
#include "Source/GameObject/GameObject3D.h"

/**
* @class Wall
* @brief 壁
* @details 簡略化のために壁を無限に長い平面とする
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
    void pushBackGameObject(Collidable3DObject& gameObject);
    /**
    * @brief ゲームオブジェクトが自身に衝突しているか
    */
    bool isHitGameObject(Collidable3DObject& gameObject);
    /**
    * @brief 描画
    */
    virtual void draw() override;
private:
    Framework::Math::Plane mPlane; //!< 平面
};