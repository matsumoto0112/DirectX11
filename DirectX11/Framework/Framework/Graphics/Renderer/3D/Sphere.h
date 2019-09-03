#pragma once
#include <memory>
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {
class VertexAndIndexBuffer;

/**
* @class Sphere
* @brief ���̃C���X�^���X
*/
class Sphere {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Sphere(UINT verticalDivide, UINT horizontalDivide);
    /**
    * @brief �f�X�g���N�^
    */
    ~Sphere();
    /**
    * @brief �`�悷��
    */
    void render(const Utility::Transform& transform);
private:
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer;
};

} //Graphics 
} //Framework 