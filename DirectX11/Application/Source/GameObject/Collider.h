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
* @brief �R���C�_�[
*/
class Collider {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Collider(const Framework::Utility::Transform& transform, GameObject3D* holder);
    /**
    * @brief �f�X�g���N�^
    */
    ~Collider();
    /**
    * @brief AABB���擾����
    */
    Framework::Math::AABB3D getAABB() const;
    /**
    * @brief OBB���擾����
    */
    Framework::Math::OBB3D getOBB() const;
    /**
    * @brief �R���C�_�[�`�揈��
    */
    void render();
    /**
    * @brief �g�����X�t�H�[���̃|�C���^���擾����
    */
    Framework::Utility::Transform* getTransformPtr() { return &mTransform; }
private:
    PROPERTY(Framework::Utility::Transform, mTransform, Transform);
    PROPERTY_POINTER(GameObject3D*, mHolder, Holder);
    PROPERTY(bool, mEnable, Enable);
private:
    std::unique_ptr<Framework::Graphics::Cube> mCollisionRendererInstance;
};