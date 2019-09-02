#pragma once
#include <memory>
#include <vector>
#include "Source/GameObject/GameObject.h"

/**
* @class GameObjectManager
* @brief discription
*/
class GameObjectManager {
    using GameObjectPtr = std::unique_ptr<GameObject>;
    using GameObjectList = std::vector<GameObjectPtr>;
public:
    /**
    * @brief コンストラクタ
    */
    GameObjectManager(GameObjectPtr player, GameObjectPtr floor);
    /**
    * @brief デストラクタ
    */
    ~GameObjectManager();
    void update();
    void draw();
    void addWall(GameObjectPtr wall);
    void addBullet(GameObjectPtr bullet);
private:
    GameObjectPtr mPlayer;
    GameObjectPtr mFloor;
    GameObjectList mWallList;
    GameObjectList mBullets;
};