#pragma once
#include <iostream>
namespace Framework {
namespace Math {

class Vector3;
class Matrix4x4;

/**
* @class Quaternion
* @brief �N�H�[�^�j�I��
*/
class Quaternion {
public:
    float x, y, z, w;
    /**
    * @brief �f�t�H���g�R���X�g���N�^
    */
    Quaternion();
    /**
    * v�e�v�f�ŏ�����
    */
    Quaternion(float x, float y, float z, float w);
    /**
    * @brief �P���l������
    */
    void identity();
    /**
    * @brief  x���ɉ�]�����p�x�ŃZ�b�g�A�b�v
    * @param theta ��]��(rad)
    */
    void setToRotateAboutX(float theta);
    /**
    * @brief  y���ɉ�]�����p�x�ŃZ�b�g�A�b�v
    * @param theta ��]��(rad)
    */
    void setToRotateAboutY(float theta);
    /**
    * @brief  z���ɉ�]�����p�x�ŃZ�b�g�A�b�v
    * @param theta ��]��(rad)
    */
    void setToRotateAboutZ(float theta);
    /**
    * @brief  Axis�����ɉ�]�����p�x�ŃZ�b�g�A�b�v
    * @param theta ��
    * @param theta ��]��(rad)
    */
    void setToRotateAboutAxis(const Vector3& axis, float theta);

    /**
    * @brief �O��
    * @detail �O�ς̌v�Z���@�𐳎��Ƃ͈Ⴄ�`�Ŏ���
    ���̗��R�ɂ��Ă͎���Ŋw�ԃQ�[���R�c���w���Q��
    */
    Quaternion operator*(const Quaternion& a) const;

    /**
    * @brief �s��ɕϊ�
    */
    Matrix4x4 toMatrix() const;

    /**
    * @brief ����
    */
    float dot(const Quaternion& a) const;

    /**
    * @brief �I�C���[�p���擾
    */
    Vector3 toEular() const;

    static Math::Quaternion conjugate(const Math::Quaternion& q);


    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);

    static Math::Quaternion createLookTarget(const Math::Vector3& v, const Math::Vector3& normal);

    Math::Vector3 multiply(const Math::Vector3& v);
};
} // Math
} //Framework 