#pragma once

#include "Framework/Math/Vector2.h"

namespace Framework {

namespace Device {
class GameDevice;
} //Device 

/**
* @class Game
* @brief ゲームクラス
*/
class Game {
protected:
    /**
    * @brief コンストラクタ
    * @param screenSize スクリーンの大きさ
    * @param title ウィンドウタイトル
    * @param isFullScreen フルスクリーンか？
    * @param fps フレームレート
    */
    Game(const Math::Vector2& screenSize, const std::string& title, bool isFullScreen = false, float fps = 60.0f);
    /**
    * @brief デストラクタ
    */
    virtual ~Game();
public:
    /**
    * @brief 実行
    */
    int run();
    /**
    * @brief 初期化
    * @return 成功したらtrueを返す
    */
    virtual bool init();
    /**
    * @brief 終了処理
    */
    virtual void finalize();

private:
    /**
    * @brief 更新
    */
    virtual void update() = 0;
    /**
    * @brief 描画
    */
    virtual void draw() = 0;
    /**
    * @brief 実行中か？
    */
    virtual bool isRunning();
private:
    //コピー禁止
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
protected:
    Math::Vector2 mScreenSize; //!< スクリーンの大きさ
    bool mIsFullScreen; //!< フルスクリーンか？
    float mFPS; //!< フレームレート
};

} //Framework 