#pragma once
#include <memory>
#include "Framework/Utility/Transform2D.h"

namespace Framework {
namespace Graphics {
class VertexAndIndexBuffer;

/**
* @class QuadInstance
* @brief �����`�`��C���X�^���X
*/
class QuadInstance {
public:
    /**
    * @brief �R���X�g���N�^
    */
    QuadInstance();
    /**
    * @brief �f�X�g���N�^
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