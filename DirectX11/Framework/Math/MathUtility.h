#pragma once
#include <initializer_list>

namespace Framework {
namespace Math {

/*! �~������*/
static const float PI = 3.1415926f;
/*! 2��*/
static const float PI2 = PI * 2;

/*! �v�Z���e�덷*/
static const float EPSILON = 0.001f;

/**
* @class MathUtility
* @brief ���w�֌W�̃��[�e�B���e�B�N���X
*/
class MathUtility {
public:
    /**
    * @brief �N�����v����
    * @tparam t �N�����v����l
    * @tparam min �����l
    * @tparam max ����l
    * @return �N�����v���ꂽ�l
    */
    template<class T>
    static T& clamp(T& t, const T& min, const T& max);

    /**
    * @brief �T�C��
    */
    static float sin(float degree);

    /**
    * @brief �R�T�C��
    */
    static float cos(float degree);

    /**
    * @brief �^���W�F���g
    */
    static float tan(float degree);

    /**
    * @brief �A�[�N�^���W�F���g
    * @return �p�x(deg)��Ԃ�
    */
    static float atan2(float y, float x);

    /**
    * @brief �A�[�N�T�C��
    * @return �p�x�ideg�j��Ԃ�
    */
    static float asin(float x);

    static float acos(float x);

    /**
    * @brief ���[�g
    */
    static float sqrt(float a);

    /**
    * @brief �R�^���W�F���g(cot)
    */
    static float cot(float degree);

    /**
    * @brief �x���烉�W�A���֕ϊ�����
    * @param deg �x
    * @return �ϊ����ꂽ���W�A��
    */
    static float toRadian(float deg);

    /**
    * @brief ���W�A������x�֕ϊ�����
    * @param rad ���W�A��
    * @return �ϊ����ꂽ�x
    */
    static float toDegree(float rad);

    /**
    * @brief ��Βl
    */
    static float abs(float X);

    /**
    * @brief ���
    * @tparam a �J�n�l
    * @tparam b �I���l
    * @tparam t ��Ԓl�i�O�`�P�j
    */
    template <class T>
    static T lerp(const T& a, const T& b, float t);

    /**
    * @brief �ő�l�̎擾
    */
    static float mymax(const std::initializer_list<float>& param);
    /**
    * @brief �ŏ��l�̎擾
    */
    static float mymin(const std::initializer_list<float>& param);
};

/**
* @brief �N�����v����
* @tparam t �N�����v����l
* @tparam min �����l
* @tparam max ����l
* @return �N�����v���ꂽ�l
*/
template<class T>
T& MathUtility::clamp(T& t, const T& min, const T& max) {
    if (t < min)t = min;
    else if (t > max) t = max;
    return t;
}

template<class T>
inline T MathUtility::lerp(const T& a, const T& b, float t) {
    //0�`1�ɃN�����v
    t = clamp(t, 0.0f, 1.0f);
    return a * (1.0f - t) + b * t;
}

} //Math
} //Framework 
