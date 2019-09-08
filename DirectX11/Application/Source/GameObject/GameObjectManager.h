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
    /**
    * @brief 更新
    */
    void update();
    /**
    * @brief 描画
    */
    void draw();
    /**
    * @brief 弾をゲームに追加する
    */
    void addBullet(BulletPtr bullet);
    /**
    * @brief 敵をゲームに追加する
    */
    void addEnemy(EnemyPtr enemy);
    /**
    * @brief プレイヤーポインタを取得する
    */
    Player* getPlayer() const { return mPlayer.get(); }
private:
    IMainSceneMediator& mMediator;
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<Field> mField;
    BulletList mBullets;
    EnemyList mEnemies;
};