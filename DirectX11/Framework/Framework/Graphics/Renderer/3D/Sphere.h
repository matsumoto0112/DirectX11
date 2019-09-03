#pragma once
#include <memory>
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {
class VertexAndIndexBuffer;

/**
* @class Sphere
* @brief 球体インスタンス
*/
class Sphere {
public:
    /**
    * @brief コンストラクタ
    */
    Sphere(UINT verticalDivide, UINT horizontalDivide);
    /**
    * @brief デストラクタ
    */
    ~Sphere();
    /**
    * @brief 描画する
    */
    void render(const Utility::Transform& transform);
private:
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer;
};

} //Graphics 
} //Framework 