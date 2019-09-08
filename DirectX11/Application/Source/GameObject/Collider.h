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
    Framework::Math::AABB3D getAABB() const;

    Framework::Math::OBB3D getOBB() const;

    void render();
    Framework::Utility::Transform* getTransformPtr() { return &mTransform; }
    Property<Framework::Utility::Transform> transform;
    /*{ mTransform,[&](const Framework::Utility::Transform& tr) {mTransform = tr; },[&]() {return mTransform; } };*/
    Property<GameObject3D*> holder;
    //{ mHolder };
private:
    GameObject3D* mHolder;
    Framework::Utility::Transform mTransform;
    std::unique_ptr<Framework::Graphics::Cube> mCollisionRendererInstance;
};