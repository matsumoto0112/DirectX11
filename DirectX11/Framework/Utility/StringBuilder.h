#pragma once

#include <string>
#include <sstream>

namespace Framework {
namespace Utility {

/**
* @class StringBuilder
* @brief ������A���N���X
*/
class StringBuilder {
public:
    /**
    * @brief �R���X�g���N�^
    * @tparam T "<<"���������Ă���C�ӂ̌^
    * @param src �A����
    */
    template <class T>
    StringBuilder(const T& src);
    /**
    * @brief �f�X�g���N�^
    */
    ~StringBuilder() = default;
    /**
    * @brief ������̌���
    */
    StringBuilder& operator<<(const StringBuilder& src);
    /**
    * @brief ������̌���
    */
    template <class T>
    StringBuilder& operator<<(const T& src);
    /**
    * @brief ���̕�����ƘA��
    */
    StringBuilder operator+(const StringBuilder& other);
    /**
    * @brief ������̎擾
    */
    const std::string& getStr() const { return s; }
    /**
    * @brief �L���X�g
    */
    operator const char*() { return s.c_str(); }
    /**
    * @brief �L���X�g
    */
    operator std::string() { return s; }
private:
    std::string s; //!< ���݂̕�����
};

template<class T>
inline StringBuilder::StringBuilder(const T& src) {
    std::stringstream ss;
    ss << src;
    s = ss.str();
}

inline StringBuilder& StringBuilder::operator<<(const Utility::StringBuilder& src) {
    s += src.s;
    return *this;
}

inline StringBuilder StringBuilder::operator+(const Utility::StringBuilder& other) {
    return StringBuilder(s + other.s);
}

template<class T>
inline StringBuilder& StringBuilder::operator<<(const T& src) {
    std::stringstream ss;
    ss << src;
    s += ss.str();
    return *this;
}

} //Utility 
} //Framework 