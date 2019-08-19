#pragma once

namespace Framework {
namespace Math {
class Vector3;
class Matrix4x4;
class Quaternion;

/**
* @class Matrix4x3
* @brief 4x3�s��
*/
class Matrix4x3 {
public:
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    float tx, ty, tz;
public:
    /**
    * @brief �P���s���ݒ肷��
    */
    void identity();
    /**
    * @brief ���s�ړ�������0�ɂ���
    */
    void zeroTranslation();
    /**
    * @brief ���s�ړ������̐ݒ�
    */
    Matrix4x3& setTranslation(const Vector3& d);
    /**
    * @brief ���s�ړ�������ݒ肵���s��̃Z�b�g�A�b�v
    */
    Matrix4x3& setupTranslation(const Vector3& d);

    /**
    * @brief X������̉�]�̃Z�b�g�A�b�v
    * @param degree ��]�ʁi�x�j
    */
    Matrix4x3& setupRotateX(float degree);
    /**
    * @brief Y������̉�]�̃Z�b�g�A�b�v
    * @param degree ��]�ʁi�x�j
    */
    Matrix4x3& setupRotateY(float degree);
    /**
    * @brief Z������̉�]�̃Z�b�g�A�b�v
    * @param degree ��]�ʁi�x�j
    */
    Matrix4x3& setupRotateZ(float degree);
    /**
    * @brief �C�ӎ�����̉�]�̃Z�b�g�A�b�v
    * @param axis ���i�P�ʃx�N�g���j
    * @param degree ��]�ʁi�x�j
    */
    Matrix4x3& setupRotate(const Vector3& axis, float degree);

    Matrix4x3& setupRotate(const Quaternion& rotate);
    /**
    * @brief �e���X�P�[�����O�s��̃Z�b�g�A�b�v
    */
    Matrix4x3& setupScale(const Vector3& s);

    friend Vector3 operator *(const Vector3& p, const Matrix4x3& m);
    friend Vector3& operator *=(Vector3& p, const Matrix4x3& m);

    /**
    * @brief 3x3�����̍s��
    */
    static float determinant(const Matrix4x3& m);

    /**
    * @brief �t�s����v�Z����
    */
    static Matrix4x3 inverse(const Matrix4x3& m);
    /**
    * @brief 4x4�s��ɕϊ�����
    */
    Matrix4x4 convertMatrix4x4() const;

    Matrix4x3 operator *(const Matrix4x3& a);
    Matrix4x3& operator *=(const Matrix4x3& a);
};

} //Math 
} //Framework 