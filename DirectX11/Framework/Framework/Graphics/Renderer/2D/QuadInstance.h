#pragma once
#include <memory>
#include "Framework/Utility/Transform2D.h"

namespace Framework {
namespace Graphics {
class VertexAndIndexBuffer;

/**
* @class QuadInstance
* @brief 長方形描画インスタンス
*/
class QuadInstance {
public:
    /**
    * @brief コンストラクタ
    */
    QuadInstance();
    /**
    * @brief デストラクタ
    */
    ~QuadInstance();
    void render();

    const Utility::Transform2D& getTransform() const { return mTransform; }
    void setTransform(const Utility::Transform2D& transform) { mTransform = transform; }
private:
    Utility::Transform2D mTransform;
    std::shared_ptr<VertexAndIndexBuffer> mBuffer;
};

} //Graphics
} //Framework