#pragma once
#include <memory>
#include <vector>
#include "Source/GameObject/GameObject.h"

class Bullet;
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
public:
    /**
    * @brief �R���X�g���N�^
    */
    GameObjectManager(IMainSceneMediator& mediator, std::unique_ptr<Player> player, std::unique_ptr<Field> field);
    /**
    * @brief �f�X�g���N�^
    */
    ~GameObjectManager();
    void update();
    void draw();
    void addBullet(BulletPtr bullet);
    void addEnemy(GameObjectPtr enemy);
private:
    IMainSceneMediator& mMediator;
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<Field> mField;
    BulletList mBullets;
    GameObjectList mEnemy;
};