#pragma once
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/FPS.h"

namespace Framework {
namespace Utility {

/**
* @class Time
* @brief 時間管理クラス
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
    /**
    * @brief フレーム開始時に呼ぶ
    */
    void startFrame();
    /**
    * @brief フレーム終了時に呼ぶ
    */
    void endFrame();
    /**
    * @brief 決まったFPSを維持するために待機する
    */
    void wait();
private:
    double mStartTime; //!< フレーム開始時間
    double mEndTime; //!< フレーム終了時間
    double mFreq; //!< 環境の周波数
    LARGE_INTEGER mCounter; //!< クロックカウント数
    float mFPS; //!< このゲームでのFPS
    FPS mFPSCounter; //!< FPS計測
private:
    PROPERTY_READONLY(float, mDeltaTime, DeltaTime);
    PROPERTY_READONLY(float, mCurrentFPS, CurrentFPS);
};

} //Utility 
} //Framework 