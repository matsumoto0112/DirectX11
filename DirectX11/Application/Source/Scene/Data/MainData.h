#pragma once
#include "Framework/Scene/SceneDataBase.h"

/**
* @class MainData
* @brief メインシーン情報クラス
*/
class MainData : public Framework::Scene::SceneDataBase {
public:
    /**
    * @brief コンストラクタ
    */
    MainData(unsigned int playerID) :mPlayerID(playerID) {}
    /**
    * @brief デストラクタ
    */
    virtual ~MainData() = default;
    /**
    * @brief プレイヤー番号の取得
    */
    unsigned int getPlayerID() const { return mPlayerID; }
    /**
    * @brief プレイヤー番号の設定
    */
    void setPlayerID(unsigned int playerID) { mPlayerID = playerID; }
private:
    unsigned int mPlayerID; //!< プレイヤー番号
};
} //Scene 