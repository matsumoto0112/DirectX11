#pragma once
#include <memory>
#include <vector>
#include "Source/GameObject/GameObject.h"

class Bullet;
class Enemy;
class Field;
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
    using BulletPtr = std::unique_ptr<Bullet>;
    using BulletList = std::vector<BulletPtr>;
    using EnemyPtr = std::unique_ptr<Enemy>;
    using EnemyList = std::vector<EnemyPtr>;
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
    void addBullet(BulletPtr bullet);
    void addEnemy(EnemyPtr enemy);
private:
    IMainSceneMediator& mMediator;
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<Field> mField;
    BulletList mBullets;
    EnemyList mEnemies;
};