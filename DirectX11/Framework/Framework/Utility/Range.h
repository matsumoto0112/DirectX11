#pragma once
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Utility {

/**
* @class Range
* @brief 範囲管理クラス
*/
template <class T>
class Range {
public:
    /**
    * @brief コンストラクタ
    */
    Range();
    /**
    * @brief コンストラクタ
    */
    Range(T min, T max);
    /**
    * @brief デストラクタ
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