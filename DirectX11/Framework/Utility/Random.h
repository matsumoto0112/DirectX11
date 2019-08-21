#pragma once

#include <random>
#include "Utility/Singleton.h"

namespace Framework {
namespace Utility {

/**
* @class Random
* @brief 乱数生成クラス
*/
class Random : public Singleton<Random> {
public:
    /**
    * @brief min以上max未満の乱数の生成
    */
    int range(int min, int max);
    /**
    * @brief min以上max以下の乱数の生成
    */
    float range(float min, float max);
protected:
    /**
    * @brief コンストラクタ
    * @details コンストラクタを外部から呼ばれないためprotected宣言
    */
    Random();
    /**
    * @brief デストラクタ
    */
    virtual ~Random();
private:
    std::random_device rnd;
    std::mt19937 mt;
    std::uniform_int_distribution<> randN;
    std::uniform_real_distribution<> randF;
};

} //Utility 
} //Framework 