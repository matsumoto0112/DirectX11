#pragma once
#include "Framework/Math/3DPrimitive/AABB3D.h"
#include "Framework/Math/3DPrimitive/OBB3D.h"
#include "Framework/Utility/Transform.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class Cube;
} //Graphics 
} //Framework 

class GameObject3D;

/**
* @class Collider
* @brief コライダー
*/
class Collider {
public:
    /**
    * @brief コンストラクタ
    */
    Collider(const Framework::Utility::Transform& transform, GameObject3D* holder);
    /**
    * @brief デストラクタ
    */
    ~Collider();
    /**
    * @brief AABBを取得する
    */
    Framework::Math::AABB3D getAABB() const;
    /**
    * @brief OBBを取得する
    */
    Framework::Math::OBB3D getOBB() const;
    /**
    * @brief コライダー描画処理
    */
    void render();
    /**
    * @brief トランスフォームのポインタを取得する
    */
    Framework::Utility::Transform* getTransformPtr() { return &mTransform; }
private:
    PROPERTY(Framework::Utility::Transform, mTransform, Transform);
    PROPERTY_POINTER(GameObject3D*, mHolder, Holder);
    PROPERTY(bool, mEnable, Enable);
private:
    std::unique_ptr<Framework::Graphics::Cube> mCollisionRendererInstance;
};