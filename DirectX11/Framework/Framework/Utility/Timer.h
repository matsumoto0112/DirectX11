#pragma once
#include <functional>
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Utility {

/**
* @class Timer
* @brief タイマークラス
*/
class Timer {
    using Event = std::function<void(void)>;
public:
    /**
    * @brief コンストラクタ
    */
    Timer(float time);
    /**
    * @brief コンストラクタ
    */
    Timer(float time, Event timerEvent);
    /**
    * @brief デストラクタ
    */
    ~Timer();
    /**
    * @brief 初期化処理
    */
    void init();
    /**
    * @brief 更新
    * @param delta 差分時間
    */
    void update(float delta);
    /**
    * @brief 時間になったか
    */
    bool isTime();
private:
    PROPERTY(float, mLimitTime, LimitTime);
    PROPERTY(float, mCurrentTime, CurrentTime);
    PROPERTY(Event, mEvent, TimeEvent);
};

} //Utility 
} //Framework 