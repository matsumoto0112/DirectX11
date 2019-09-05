#pragma once
#include <memory>
#include <vector>
#include "Source/GameObject/GameObject.h"

class IMainSceneMediator;
class Player;
class Wall;
class Field;

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
    GameObjectManager(IMainSceneMediator& mediator, std::unique_ptr<Player> player, std::unique_ptr<Field> field);
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
    std::unique_ptr<Field> mField;
    GameObjectList mBullets;
    GameObjectList mEnemy;
};