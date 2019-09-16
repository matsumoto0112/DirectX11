#pragma once
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Utility {

/**
* @class Range
* @brief �͈͊Ǘ��N���X
*/
template <class T>
class Range {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Range();
    /**
    * @brief �R���X�g���N�^
    */
    Range(T min, T max);
    /**
    * @brief �f�X�g���N�^
    */
    ~Range();
private:
    PROPERTY(T, mMin, Min);
    PROPERTY(T, mMax, Max);
};

template<class T>
inline Range<T>::Range()
    :mMin(), mMax() {}

template<class T>
inline Range<T>::Range(T min, T max)
    : mMin(min), mMax(max) {}

template<class T>
inline Range<T>::~Range() {}

} //Utility 
} //Framework 