#pragma once
#include <array>
#include "Framework/Math/Vector3.h"
namespace Framework {
namespace Math {

struct OBB3D {
public:
    Vector3 mPosition; //!< �ʒu
    std::array<Vector3, 3> mNormalDirect; //!< �e���̕����x�N�g��
    Vector3 mLength;
public:
    /**
    * @brief �f�t�H���g�R���X�g���N�^
    */
    OBB3D() :OBB3D(Vector3::ZERO, { Vector3::RIGHT,Vector3::UP,Vector3::FORWORD }, { 1.0f,1.0f,1.0f }) {}
    /**
    * @brief �R���X�g���N�^
    * @param position ���W
    * @param normals �e���̐��K�����ꂽ�����x�N�g��
    * @param lengths �e���̒��S����̒���
    */
    OBB3D(const Vector3& position, const std::array<Vector3, 3>& normal, const Vector3& length)
        :mPosition(position), mNormalDirect(normal), mLength(length) {}
    /**
    * @brief �Փ˂��Ă��邩
    * @param other ����OBB
    * @return �Փ˂��Ă�����true��Ԃ�
    */
    bool isCollide(const OBB3D& other) const;

    void setPosition(const Math::Vector3& position);
    void setNormal(int axis, const Math::Vector3& normal);
    void setLength(const Math::Vector3& length);
};

} //Math 
} //Framework 