#pragma once
#include <memory>
#include <vector>
#include "Source/GameObject/GameObject.h"

namespace Framework {
namespace Graphics {
class IRenderer;
} //Graphics
} //Framework 

class Bullet;
class Enemy;
class Field;
class IMainSceneMediator;
class Item;
class Player;
class Wall;

/**
* @class GameObjectManager
* @brief ゲームオブジェクト管理者
*/
class GameObjectManager {
    using GameObjectPtr = std::unique_ptr<GameObject>;
    using GameObjectList = std::vector<GameObjectPtr>;
    using BulletPtr = std::unique_ptr<Bullet>;
    using BulletList = std::vector<BulletPtr>;
    using EnemyPtr = std::unique_ptr<Enemy>;
    using EnemyList = std::vector<EnemyPtr>;
    using ItemPtr = std::unique_ptr<Item>;
    using ItemList = std::vector<ItemPtr>;
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
    * @param renderer 描画デバイス
    */
    void draw(Framework::Graphics::IRenderer* renderer);
    /**
    * @brief 描画
    */
    void draw(int phase = 0);
    /**
    * @brief 弾をゲームに追加する
    */
    void addBullet(BulletPtr bullet);
    /**
    * @brief 敵をゲームに追加する
    */
    void addEnemy(EnemyPtr enemy);
    /**
    * @brief アイテムをゲームに追加する
    */
    void addItem(ItemPtr item);
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
    ItemList mItems;
};