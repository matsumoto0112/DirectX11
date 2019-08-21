#pragma once

#include <ostream>
#include "Framework/Math/MathUtility.h"

namespace Framework {
namespace Math {

/**
* @class Vector3
* @brief Vector3�N���X
*/
class Vector3 {
public:
    float x; //!< x
    float y; //!< y
    float z; //!< z
public:
    static const Vector3 ZERO;
    static const Vector3 LEFT;
    static const Vector3 RIGHT;
    static const Vector3 UP;
    static const Vector3 DOWN;
    static const Vector3 FORWORD;
    static const Vector3 BACK;
public:
    /**
    * @brief �R���X�g���N�^
    */
    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    /**
    * @brief �R�s�[�R���X�g���N�^
    */
    Vector3(const Vector3& v);
    /**
    * @brief ������Z�q
    */
    Vector3& operator =(const Vector3& a);

    /**
    * @brief ���l���Z�q
    */
    bool operator ==(const Vector3 &a) const;
    /**
    * @brief ���l���Z�q
    */
    bool operator !=(const Vector3 &a) const;
    /**
    * @brief 0�x�N�g���̎擾
    */
    static Vector3 zero();
    /**
    * @brief �P���v���X���Z�q
    */
    Vector3 operator +() const;
    /**
    * @brief �P���}�C�i�X���Z�q
    */
    Vector3 operator -() const;
    /**
    * @brief ���Z
    */
    Vector3 operator +(const Vector3 &a) const;
    /**
    * @brief ���Z
    */
    Vector3 operator -(const Vector3 &a) const;
    /**
    * @brief �X�J���[�{
    */
    Vector3 operator *(float a) const;
    /**
    * @brief �X�J���[���Z
    */
    Vector3 operator /(float a) const;
    /**
    * @brief �X�J���[�{
    */
    friend Vector3 operator *(float a, const Vector3& v);
    /**
    * @brief �X�J���[���Z
    */
    friend Vector3 operator /(float a, const Vector3& v);
    /**
    * @brief ���Z������Z�q
    */
    Vector3 &operator +=(const Vector3 &a);
    /**
    * @brief ���Z������Z�q
    */
    Vector3 &operator -=(const Vector3 &a);
    /**
    * @brief ��Z������Z�q
    */
    Vector3 &operator *=(float a);
    /**
    * @brief ���Z������Z�q
    */
    Vector3 &operator /=(float a);

    /**
    * @brief �傫����2���Ԃ�
    * @return �x�N�g���̑傫����2��
    */
    float lengthSq() const;
    /**
    * @brief �傫����Ԃ�
    * @return �x�N�g���̑傫��
    */
    float length() const;
    /**
    * @brief �x�N�g���𐳋K������
    */
    void normalize();
    /**
    * @brief �x�N�g���̐��K��
    * @return ���K�����ꂽ�x�N�g����Ԃ�
    */
    Vector3 getNormal() const;
    /**
    * @brief ����
    * @param a �v�Z����x�N�g��
    * @return ����
    */
    float dot(const Vector3 &a) const;
    /**
    * @brief �O��
    * @param a �v�Z����x�N�g��
    * @return �O��
    */
    Vector3 cross(const Vector3 &a) const;
    /**
    * @brief �x�N�g���̃N�����v����
    * @param min ����
    * @param max ���
    */
    void clamp(const Vector3& min, const Vector3& max);

    /**
    * @brief ����
    * @param a a�x�N�g��
    * @param b b�x�N�g��
    */
    static float dot(const Vector3 &a, const Vector3 &b);
    /**
    * @brief �O��
    * @param a a�x�N�g��
    * @param b b�x�N�g��
    */
    static Vector3 cross(const Vector3 &a, const Vector3 &b);

    /**
    * @brief �X�g���[�����Z�q
    */
    friend std::ostream& operator<<(std::ostream& os, const Math::Vector3& v);

};

} //Math
} //Framework 