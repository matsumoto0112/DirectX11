#pragma once
#include <memory>
#include <vector>
#include "Source/GameObject/GameObject.h"

class IMainSceneMediator;
class Player;
class Wall;

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
    GameObjectManager(IMainSceneMediator& mediator, std::unique_ptr<Player> player, GameObjectPtr floor);
    /**
    * @brief デストラクタ
    */
    ~GameObjectManager();
    void update();
    void draw();
    void addWall(std::unique_ptr<Wall> wall);
    void addBullet(GameObjectPtr bullet);
    void addEnemy(GameObjectPtr enemy);
private:
    IMainSceneMediator& mMediator;
    std::unique_ptr<Player> mPlayer;
    GameObjectPtr mFloor;
    std::vector<std::unique_ptr<Wall>> mWallList;
    GameObjectList mBullets;
    GameObjectList mEnemy;
};