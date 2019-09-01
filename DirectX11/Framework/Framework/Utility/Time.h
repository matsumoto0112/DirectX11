#pragma once
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/FPS.h"

namespace Framework {
namespace Utility {

/**
* @class Time
* @brief discription
*/
class Time :public Singleton<Time> {
public:
    /**
    * @brief コンストラクタ
    */
    Time();
    /**
    * @brief デストラクタ
    */
    ~Time();
    /**
    * @brief 初期化処理
    * @param fps このゲームのFPS
    */
    void init(float fps);
    void update();
private:
    float mFPS; //!< このゲームでのFPS
    FPS mFPSCounter; //!< FPS計測
    PROPERTY_READONLY(float, mDeltaTime, DeltaTime);
};

} //Utility 
} //Framework 