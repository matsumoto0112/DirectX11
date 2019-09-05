#pragma once
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Math {

/**
* @class AABB3D
* @brief 3DAABB
*/
class AABB3D {
private:
    Vector3 mMin;
    Vector3 mMax;
public:
    Property<Vector3> min{ mMin };
    Property<Vector3> max{ mMax };
public:
    /**
    * @brief �f�t�H���g�R���X�g���N�^
    */
    AABB3D();
    /**
    * @brief �R���X�g���N�^
    */
    AABB3D(const Vector3& min, const Vector3& max);
    /**
    * @brief �f�X�g���N�^
    */
    ~AABB3D();
    /**
    * @brief �傫�����擾����
    */
    Vector3 size() const { return mMax - mMin; }
    /**
    * @brief X�̑傫�����擾����
    */
    float xSize() const { return mMax.x - mMin.x; }
    /**
    * @brief Y�̑傫�����擾����
    */
    float ySize() const { return mMax.y - mMin.y; }
    /**
    * @brief Z�̑傫�����擾����
    */
    float zSize() const { return mMax.z - mMin.z; }
    /**
    * @brief ���S���W���擾����
    */
    Vector3 center() const { return (mMax + mMin) * 0.5f; }
    /**
    * @brief �{�b�N�X�ɓ_��ǉ�����
    */
    void add(const Vector3& p);
    /**
    * @brief box�����W�ϊ��������AABB���\�z����
    */
    void setToTransformedAABB(const AABB3D& box, const Matrix4x4& m);
    /**
    * @brief �_���܂�ł��邩
    */
    bool contains(const Vector3& p) const;
    /**
    * @brief ���AABB���d�Ȃ��Ă��邩
    */
    static bool intersect(const AABB3D& box1, const AABB3D& box2);
};

} //Math 
} //Framework 