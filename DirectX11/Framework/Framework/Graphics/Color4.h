#pragma once

#include <array>

namespace Framework {
namespace Graphics {
/**
* @class Color4
* @brief �F
*/
class Color4 {
public:
    float r; //!< r����
    float g; //!< g����
    float b; //!< b����
    float a; //!< a����
public:
    static const Color4 BLACK; //!< ��
    static const Color4 WHITE; //!< ��
public:
    /**
    * @brief �R���X�g���N�^
    */
    Color4();
    /**
    * @brief �R���X�g���N�^
    * @param r r����(0.0�`1.0)
    * @param g g����(0.0�`1.0)
    * @param b b����(0.0�`1.0)
    * @param a a����(0.0�`1.0)
    */
    Color4(float r, float g, float b, float a);
    /**
    * @brief �R���X�g���N�^
    * @param color �F�z��
    */
    Color4(float color[4]);
    /**
    * @brief �R�s�[�R���X�g���N�^
    */
    Color4(const Color4& c);
    /**
    * @brief �f�X�g���N�^
    */
    ~Color4();
    /**
    * @brief ������Z�q
    */
    Color4& operator=(const Color4& c);
    /**
    * @brief ���l���Z�q
    */
    bool operator==(const Color4& c);
    /**
    * @brief ���l���Z�q
    */
    bool operator!=(const Color4& c);
    /**
    * v�P���v���X���Z�q
    */
    Color4 operator+();
    /**
    * @brief �P���}�C�i�X���Z�q
    */
    Color4 operator-();

    /**
    * @brief �z��̎擾
    * @param c �߂�l
    */
    void get(float c[4]) const;

    /**
    * @brief �F��z��Ŏ擾
    * @return r,g,b,a�̏��Ɋi�[���ꂽ�z��
    */
    std::array<float, 4> get() const;

    /**
    * @brief ���
    * @param a �F1
    * @param b �F2
    * @param t ��ԌW��
    */
    static Color4 lerp(const Color4& a, const Color4& b, float t);
};

} //Graphics 
} //Framework 
