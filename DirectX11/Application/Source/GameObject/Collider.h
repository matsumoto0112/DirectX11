#pragma once
#include "Framework/Math/AABB3D.h"
#include "Framework/Math/Primitive3D.h"
#include "Framework/Utility/Transform.h"

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

    void render();
private:
    Framework::Utility::Transform mTransform;
    std::unique_ptr<Framework::Graphics::Cube> mCollisionRendererInstance;
};