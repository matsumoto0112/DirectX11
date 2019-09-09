#include "GameObjectManager.h"
#include "Framework/Utility/Collision.h"
#include "Source/GameObject/Bullet/Bullet.h"
#include "Source/GameObject/Collider.h"
#include "Source/GameObject/Enemy/Enemy.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Source/GameObject/Item/Item.h"
#include "Source/GameObject/Player.h"
#include "Source/GameObject/Field.h"

using namespace Framework;
namespace {
template <class T>
void eraseGameObjectIfNotAlive(std::vector<T>& list) {
    auto removeIt = std::remove_if(list.begin(), list.end(), [](auto&& obj) {return !obj->getIsAlive(); });
    list.erase(removeIt, list.end());
}
}

GameObjectManager::GameObjectManager(IMainSceneMediator& mediator, std::unique_ptr<Player> player, std::unique_ptr<Field> field)
    :mMediator(mediator), mPlayer(std::move(player)), mField(std::move(field)) {
    mPlayer->initialize();
}

GameObjectManager::~GameObjectManager() {
    mBullets.clear();
}

void GameObjectManager::update() {
    mPlayer->update();
    for (auto&& bullet : mBullets) {
        bullet->update();
    }
    for (auto&& enemy : mEnemies) {
        enemy->update();
    }
    for (auto&& item : mItems) {
        item->update();
    }

    for (auto&& bullet : mBullets) {
        for (auto&& enemy : mEnemies) {
            if (bullet->getColliderPtr()->getOBB().isCollide(enemy->getColliderPtr()->getOBB())) {
                bullet->dispatch(enemy.get());
                enemy->dispatch(bullet.get());
            }
        }
    }

    for (auto&& item : mItems) {
        if (item->getColliderPtr()->getOBB().isCollide(mPlayer->getColliderPtr()->getOBB())) {
            item->dispatch(mPlayer.get());
            mPlayer->dispatch(item.get());
        }
    }

    mField->pushBackGameObject(*mPlayer);

    for (auto&& bullet : mBullets) {
        if (mField->isGameObjectOutOfArea(*bullet)) {
            bullet->outOfArea();
        }
    }

    eraseGameObjectIfNotAlive(mEnemies);
    eraseGameObjectIfNotAlive(mBullets);
    eraseGameObjectIfNotAlive(mItems);
}

void GameObjectManager::draw() {
    mField->draw();
    mPlayer->draw();
    for (auto&& bullet : mBullets) {
        bullet->draw();
    }
    for (auto&& enemy : mEnemies) {
        enemy->draw();
    }
    for (auto&& item : mItems) {
        item->draw();
    }
}

void GameObjectManager::addBullet(BulletPtr bullet) {
    bullet->initialize();
    mBullets.emplace_back(std::move(bullet));
}

void GameObjectManager::addEnemy(EnemyPtr enemy) {
    enemy->initialize();
    mEnemies.emplace_back(std::move(enemy));
}

void GameObjectManager::addItem(ItemPtr item) {
    item->initialize();
    mItems.emplace_back(std::move(item));
}
