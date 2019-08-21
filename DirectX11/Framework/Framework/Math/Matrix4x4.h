#pragma once

#include <array>
#include <ostream>
#include "Framework/Math/Vector3.h"
namespace Framework {
namespace Math {

class Vector2;
class Matrix3x3;
class Quaternion;

/**
* @class Matrix4x4
* @brief 4*4�s��
*/
class Matrix4x4 {
public:
    std::array<std::array<float, 4>, 4> m; //!< 4x4�s��
    /**
    * @brief �R���X�g���N�^
    */
    Matrix4x4();
    /**
    * @brief �R���X�g���N�^
    */
    Matrix4x4(float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44);
    /**
    * @brief �R���X�g���N�^
    */
    Matrix4x4(std::array<std::array<float, 4>, 4> m);
    /**
    * @brief �P�ʍs��
    */
    void loadIdentity();
    /**
    * @brief �P�ʍs���Ԃ�
    */
    static Matrix4x4 identity();
    /**
    * @brief ������Z�q
    */
    Matrix4x4& operator=(const Matrix4x4& mat);
    /**
    * @brief ���l���Z�q
    */
    bool operator==(const Matrix4x4& mat) const;
    /**
    * @brief ���l���Z�q
    */
    bool operator!=(const Matrix4x4& mat) const;
    /**
    * @brief �P���v���X���Z�q
    */
    Matrix4x4 operator+();
    /**
    * @brief �P���}�C�i�X���Z�q
    */
    Matrix4x4 operator-();
    /**
    * @brief ���Z
    */
    Matrix4x4 operator+(const Matrix4x4& mat) const;
    /**
    * @brief ���Z
    */
    Matrix4x4 operator-(const Matrix4x4& mat) const;
    /**
    * @brief �X�J���[�{
    */
    Matrix4x4 operator*(float k) const;
    /**
    * @brief ��Z
    */
    Matrix4x4 operator*(const Matrix4x4& mat) const;
    /**
    * @brief �x�N�g���~�s��
    */
    friend Vector3 operator*(const Vector3& v, const Matrix4x4& mat);
    /**
    * @brief �X�J���[���Z
    */
    Matrix4x4 operator/(float k) const;
    /**
    * @brief ���Z������Z�q
    */
    Matrix4x4& operator+=(const Matrix4x4& mat);
    /**
    * @brief ���Z������Z�q
    */
    Matrix4x4& operator-=(const Matrix4x4& mat);
    /**
    * @brief ��Z������Z�q
    */
    Matrix4x4& operator*=(float k);
    /**
    * @brief ��Z������Z�q
    */
    Matrix4x4& operator*=(const Matrix4x4& mat);
    /**
    * @brief �x�N�g���~�s��
    */
    friend Vector3& operator*=(Vector3& v, const Matrix4x4& mat);
    /**
    * @brief ���Z������Z�q
    */
    Matrix4x4& operator/=(float k);

    /**
    * @brief ���s�ړ��s��̍쐬
    * @param v �ړ���
    */
    static Matrix4x4 createTranslate(const Vector3& v);
    /**
    * @brief ���s�ړ��s��̍쐬
    * @param x �ړ���X
    * @param y �ړ���Y
    * @param z �ړ���Z
    */
    static Matrix4x4 createTranslate(float x, float y, float z);
    /**
    * @brief ���s�ړ��s��̃Z�b�g�A�b�v
    * @param v �ړ���
    */
    Matrix4x4& setupTransform(const Vector3& v);
    /**
    * @brief ���s�ړ��s��̃Z�b�g�A�b�v
    * @param x �ړ���X
    * @param y �ړ���Y
    * @param z �ړ���Z
    */
    Matrix4x4& setupTransform(float x, float y, float z);

    /**
    * @brief ���s�ړ�
    * @param v �ړ���
    * @return ���̍s�񂩂炳���v�ړ�������̍s���Ԃ�
    */
    Matrix4x4& move(const Vector3& v);

    /**
    * @brief ���s�ړ�
    * @param x �ړ���X
    * @param y �ړ���Y
    * @param z �ړ���Z
    * @return ���̍s�񂩂炳���(x,y,z)�ړ�������̍s���Ԃ�
    */
    Matrix4x4& move(float x, float y, float z);

    /**
    * @brief X����]�s��̍쐬
    * @param degree ��]��(�x)
    */
    static Matrix4x4 createRotationX(float degree);
    /**
    * @brief X����]�s��̃Z�b�g�A�b�v
    * @param degree ��]��(�x)
    */
    Matrix4x4& setupRotationX(float degree);
    /**
    * @brief Y����]�s��̍쐬
    * @param degree ��]��(�x)
    */
    static Matrix4x4 createRotationY(float degree);
    /**
    * @brief Y����]�s��̃Z�b�g�A�b�v
    * @param degree ��]��(�x)
    */
    Matrix4x4& setupRotationY(float degree);
    /**
    * @brief Z����]�s��̍쐬
    * @param degree ��]��(�x)
    */
    static Matrix4x4 createRotationZ(float degree);
    /**
    * @brief Z����]�s��̃Z�b�g�A�b�v
    * @param degree ��]��(�x)
    */
    Matrix4x4& setupRotationZ(float degree);
    /**
    * @brief ��]�s��̍쐬
    * @param r �e���̉�]��(�x)
    */
    static Matrix4x4 createRotation(const Vector3& r);
    /**
    * @brief ��]�s��̃Z�b�g�A�b�v
    * @param r �e���̉�]��(�x)
    */
    Matrix4x4& setupRotation(const Vector3& r);
    /**
    * @brief X����]
    * @param degree ��]��(�x)
    * @return ���̍s�񂩂炳���degree�x��]����s���Ԃ�
    */
    Matrix4x4& rotateX(float degree);
    /**
    * @brief Y����]
    * @param degree ��]��(�x)
    * @return ���̍s�񂩂炳���degree�x��]����s���Ԃ�
    */
    Matrix4x4& rotateY(float degree);
    /**
    * @brief Z����]
    * @param degree ��]��(�x)
    * @return ���̍s�񂩂炳���degree�x��]����s���Ԃ�
    */
    Matrix4x4& rotateZ(float degree);
    /**
    * @brief ��]
    * @param r �e���̉�]��(�x)
    * @return ���̍s�񂩂炳���v�x��]����s���Ԃ�
    */
    Matrix4x4& rotate(const Vector3& v);

    /**
    * @brief �g��E�k���s��̍쐬
    * @param s �g��E�k���̑傫��(�e������)
    */
    static Matrix4x4 createScale(float s);
    /**
    * @brief �g��E�k���s��̍쐬
    * @param s �e���̊g��E�k���̑傫��
    */
    static Matrix4x4 createScale(const Vector3& s);
    /**
    * @brief �g��E�k���s��̃Z�b�g�A�b�v
    * @param s �g��E�k���̑傫��(�e������)
    */
    Matrix4x4& setupScale(float s);
    /**
    * @brief �g��E�k���s��̃Z�b�g�A�b�v
    * @param s �e���̊g��E�k���̑傫��
    */
    Matrix4x4& setupScale(const Vector3& s);
    /**
    * @brief �g��E�k���s��̍쐬
    * @param sx x���̊g��E�k���̑傫��
    * @param sy y���̊g��E�k���̑傫��
    * @param sz z���̊g��E�k���̑傫��
    */
    static Matrix4x4 createScale(float sx, float sy, float sz);
    /**
    * @brief �g��E�k���s��
    * @param s �g��E�k���̑傫��(�e������)
    * @return ���̍s�񂩂炳���s�{�g�傷��s���Ԃ�
    */
    Matrix4x4& scale(float s);
    /**
    * @brief �g��E�k���s��
    * @param s �e���̊g��E�k���̑傫��
    * @return ���̍s�񂩂炳���s�{�g�傷��s���Ԃ�
    */
    Matrix4x4& scale(const Vector3& s);

    /**
    * @brief �r���[�s��̍쐬
    * @param eye ���_
    * @param at �����_
    * @param up �J�����̏����
    */
    static Matrix4x4 createView(const Vector3& eye, const Vector3& at, const Vector3& up);

    /**
    * @brief �r���[�s��̃Z�b�g�A�b�v
    * @param eye ���_
    * @param at �����_
    * @param up �J�����̏����
    */
    Matrix4x4& setUpView(const Vector3& eye, const Vector3& at, const Vector3& up);

    /**
    * @brief �v���W�F�N�V�����s��̍쐬
    * @param fovY ����p(�x)
    * @param screenX �X�N���[���̕�
    * @param screenY �X�N���[���̍���
    * @param near �ŋߓ_
    * @param far �ŉ��_
    */
    static Matrix4x4 createProjection(float fovY, float screenX, float screenY, float near, float far);

    /**
    * @brief �v���W�F�N�V�����s��̃Z�b�g�A�b�v
    * @param fovY ����p(�x)
    * @param screenX �X�N���[���̕�
    * @param screenY �X�N���[���̍���
    * @param near �ŋߓ_
    * @param far �ŉ��_
    */
    Matrix4x4& setProjection(float fovY, float screenX, float screenY, float near, float far);

    Math::Vector3 getTranslate();

    /**
    * @brief �����e�s��̍쐬
    * @param screenSize ��ʂ̑傫��
    */
    static Matrix4x4 createOrthographic(const Vector2& screenSize);
    /**
    * @brief �����e�s��̃Z�b�g�A�b�v
    * @param screenSize ��ʂ̑傫��
    */
    Matrix4x4& setUpOrthographic(const Vector2& screenSize);

    /**
    * @brief �l�����ɕϊ�
    */
    Quaternion toQuaternion() const;

    /**
    * @brief �]�u����
    */
    Matrix4x4& transpose();

    /**
    * @brief �]�u�s��
    */
    static Matrix4x4 transposition(const Matrix4x4& mat);
    /**
    * @brief �s�񎮂����߂�
    * @param mat ���߂�s��
    */
    static float determinant(const Matrix4x4& mat);
    /**
    * @brief �t�s������߂�
    * @param mat ���߂�s��
    */
    static Matrix4x4 inverse(const Matrix4x4& mat);

    /**
    * @brief 3*3�s��ɕϊ�(�]���ȃf�[�^�؂�̂�)
    */
    static Matrix3x3 toMatrix3(const Matrix4x4& mat);

    static Matrix4x4 lerp(const Matrix4x4& mat1, const Matrix4x4& mat2, float t);

    friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat);
};

} //Math
} //Framework 