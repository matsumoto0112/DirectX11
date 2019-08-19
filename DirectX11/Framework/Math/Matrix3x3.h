#pragma once

#include <array>
#include "Math/Vector2.h"
namespace Framework {
namespace Math {

class Matrix4x4;

/**
* @class Matrix3x3
* @brief 3*3�s��
*/
class Matrix3x3 {
public:
    std::array<std::array<float, 3>, 3> m; //!< 3x3�s��
    /**
    * @brief �R���X�g���N�^
    */
    Matrix3x3();
    /**
    * @brief �����t���R���X�g���N�^
    */
    Matrix3x3(float m11, float m12, float m13,
        float m21, float m22, float m23,
        float m31, float m32, float m33);
    /**
    * @brief �����t���R���X�g���N�^
    */
    Matrix3x3(std::array<std::array<float, 3>, 3> m);
    /**
    * @brief �P�ʍs��
    */
    void loadIdentity();
    /**
    * @brief �P�ʍs���Ԃ�
    */
    static Matrix3x3 identity();
    /**
    * v������Z�q
    */
    Matrix3x3& operator=(const Matrix3x3& mat);
    /**
    * @brief ���l���Z�q
    */
    bool operator==(const Matrix3x3& mat) const;
    /**
    * @brief ���l���Z�q
    */
    bool operator!=(const Matrix3x3& mat) const;
    /**
    * @brief �P���v���X���Z�q
    */
    Matrix3x3 operator+();
    /**
    * @brief �P���}�C�i�X���Z�q
    */
    Matrix3x3 operator-();
    /**
    * @brief ���Z
    */
    Matrix3x3 operator+(const Matrix3x3& mat);
    /**
    * @brief ���Z
    */
    Matrix3x3 operator-(const Matrix3x3& mat);
    /**
    * @brief �X�J���[�{
    */
    Matrix3x3 operator*(float k);
    /**
    * @brief ��Z
    */
    Matrix3x3 operator*(const Matrix3x3& mat);
    /**
    * @brief �x�N�g���~�s��
    */
    friend Vector2 operator*(const Vector2& v, const Matrix3x3& mat);
    /**
    * @brief �X�J���[���Z
    */
    Matrix3x3 operator/(float k);
    /**
    * @brief ���Z������Z�q
    */
    Matrix3x3& operator+=(const Matrix3x3& mat);
    /**
    * @brief ���Z������Z�q
    */
    Matrix3x3& operator-=(const Matrix3x3& mat);
    /**
    * @brief ��Z������Z�q
    */
    Matrix3x3& operator*=(float k);
    /**
    * @brief ��Z������Z�q
    */
    Matrix3x3& operator*=(const Matrix3x3& mat);
    /**
    * @brief �x�N�g���~�s��
    */
    friend Vector2& operator*=(Vector2& v, const Matrix3x3& mat);
    /**
    * @brief ���Z������Z�q
    */
    Matrix3x3& operator/=(float k);

    /**
    * @brief ���s�ړ��s��̍쐬
    * @param v �ړ���
    */
    static Matrix3x3 createTranslate(const Vector2& v);
    /**
    * @brief ���s�ړ��s��̍쐬
    * @param x �ړ���X
    * @param y �ړ���Y
    */
    static Matrix3x3 createTranslate(float x, float y);

    /**
    * @brief ���s�ړ�
    * @param v �ړ���
    * @return ���̍s�񂩂炳���v�ړ�������̍s���Ԃ�
    */
    Matrix3x3& transform(const Vector2& v);

    /**
    * @brief ���s�ړ�
    * @param x �ړ���X
    * @param y �ړ���Y
    * @return ���̍s�񂩂炳���(x,y)�ړ�������̍s���Ԃ�
    */
    Matrix3x3& transform(float x, float y);

    /**
    * @brief ��]�s��̍쐬
    * @param degree ��]��(�x)
    */
    static Matrix3x3 createRotate(float degree);
    /**
    * @brief ��]
    * @param degree ��]��(�x)
    * @return ���̍s�񂩂炳���degree�x��]������̍s���Ԃ�
    */
    Matrix3x3& rotate(float degree);

    /**
    * @brief �g��E�k���s��̍쐬
    * @param s �g��E�k���̑傫��(�e������)
    */
    static Matrix3x3 createScale(float s);
    /**
    * @brief �g��E�k���s��̍쐬
    * @param s �e���̊g��E�k���̑傫��
    */
    static Matrix3x3 createScale(const Vector2& s);

    /**
    * @brief �g��E�k���s��
    * @param s �g��E�k���̑傫��(�e������)
    * @return ���̍s�񂩂炳���s�{�g�傷��s���Ԃ�
    */
    Matrix3x3& scale(float s);
    /**
    * @brief �g��E�k���s��
    * @param s �e���̊g��E�k���̑傫��
    * @return ���̍s�񂩂炳���s�{�g�傷��s���Ԃ�
    */
    Matrix3x3& scale(const Vector2& s);

    /**
    * @brief 4*4�s��ւ̕ϊ�
    * @details ���s�ړ������͂Ȃ�
    */
    static Matrix4x4 toMatrix4(const Matrix3x3& mat);
};
} //Math
} //Framework 