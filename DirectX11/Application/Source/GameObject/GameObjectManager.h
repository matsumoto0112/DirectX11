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
* @brief �Q�[���I�u�W�F�N�g�Ǘ���
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
    * @brief �R���X�g���N�^
    */
    GameObjectManager(IMainSceneMediator& mediator, std::unique_ptr<Player> player, std::unique_ptr<Field> field);
    /**
    * @brief �f�X�g���N�^
    */
    ~GameObjectManager();
    /**
    * @brief �X�V
    */
    void update();
    /**
    * @brief �`��
    * @param renderer �`��f�o�C�X
    */
    void draw(Framework::Graphics::IRenderer* renderer);
    /**
    * @brief �`��
    */
    void draw(int phase = 0);
    /**
    * @brief �e���Q�[���ɒǉ�����
    */
    void addBullet(BulletPtr bullet);
    /**
    * @brief �G���Q�[���ɒǉ�����
    */
    void addEnemy(EnemyPtr enemy);
    /**
    * @brief �A�C�e�����Q�[���ɒǉ�����
    */
    void addItem(ItemPtr item);
    /**
    * @brief �v���C���[�|�C���^���擾����
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