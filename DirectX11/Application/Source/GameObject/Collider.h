#pragma once
#include "Framework/Math/AABB3D.h"
#include "Framework/Math/OBB3D.h"
#include "Framework/Utility/Transform.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class Cube;
} //Graphics 
} //Framework 

/**
* @class Collider
* @brief コライダー
*/
class Collider {
public:
    /**
    * @brief コンストラクタ
    */
    Collider(const Framework::Utility::Transform& transform);
    /**
    * @brief デストラクタ
    */
    ~Collider();
    Framework::Math::AABB3D getAABB() const;

    Framework::Math::OBB3D getOBB() const;

    void render();
    Property<Framework::Utility::Transform> transform{ mTransform,[&](const Framework::Utility::Transform& tr) {mTransform = tr; },[&]() {return mTransform; } };
private:
    Framework::Utility::Transform mTransform;
    std::unique_ptr<Framework::Graphics::Cube> mCollisionRendererInstance;
};