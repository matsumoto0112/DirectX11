#pragma once
namespace Framework {
namespace Math {

/**
* @class IntVector2
* @brief �����^Vector2
*/
class IntVector2 {
public:
    int x; //!< x����
    int y; //!< y����
public:
    /**
    * @brief �R���X�g���N�^
    */
    IntVector2(int x = 0, int y = 0);
    /**
    * @brief �R�s�[�R���X�g���N�^
    */
    IntVector2(const IntVector2& i);
    /**
    * @brief �f�X�g���N�^
    */
    ~IntVector2();

    /**
    * @brief ������Z�q
    */
    IntVector2& operator=(const IntVector2& i);

    /**
    * @brief ���l���Z�q
    */
    bool operator==(const IntVector2& i)const;
    /**
    * @brief ���l���Z�q
    */
    bool operator !=(const IntVector2& i) const;
    /**
    * @brief 0�x�N�g���̎擾
    */
    static IntVector2 zero();
    /**
    * @brief �P���v���X���Z�q
    */
    IntVector2 operator +() const;
    /**
    * @brief �P���}�C�i�X���Z�q
    */
    IntVector2 operator -() const;
    /**
    * @brief ���Z
    */
    IntVector2 operator +(const IntVector2& i) const;
    /**
    * @brief ���Z
    */
    IntVector2 operator -(const IntVector2& i) const;
    /**
    * @brief �X�J���[�{
    */
    IntVector2 operator *(float s) const;
    /**
    * @brief �X�J���[�{
    */
    friend IntVector2 operator *(float s, const IntVector2& i);
    /**
    * @brief �X�J���[���Z
    */
    IntVector2 operator /(float s) const;
    /**
    * @brief �X�J���[���Z
    */
    friend IntVector2 operator /(float s, const IntVector2& i);
    /**
    * @brief ���Z������Z�q
    */
    IntVector2& operator +=(const IntVector2& v);
    /**
    * @brief ���Z������Z�q
    */
    IntVector2& operator -=(const IntVector2& v);
    /**
    * @brief ��Z������Z�q
    */
    IntVector2& operator *=(float s);
    /**
    * @brief ���Z������Z�q
    */
    IntVector2& operator /=(float s);
};

} //Math 
} //Framework 