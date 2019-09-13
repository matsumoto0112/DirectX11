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
/**
* @brief 生存していないゲームオブジェクトを削除する
*/
template <class T>
void eraseGameObjectIfNotAlive(std::vector<T>& list) {
    auto removeIt = std::remove_if(list.begin(), list.end(), [](auto&& obj) {return !obj->getIsAlive(); });
    list.erase(removeIt, list.end());
}

/**
* @brief コライダー同士が衝突しているか
*/
bool isHitCollider(Collider* col1, Collider* col2) {
    return col1->getOBB().isCollide(col2->getOBB());
}

/**
* @brief リストとゲームオブジェクトの衝突を解決
*/
template<class T, class T2>
void solveCollideObjectToList(T* gameObject, std::vector<T2>& list) {
    //ゲームオブジェクトのコライダーが有効か調べる
    Collider* gameObjectCollider = gameObject->getColliderPtr();
    if (!gameObjectCollider->getEnable())return;
    for (auto&& obj : list) {
        //リストのオブジェクトのコライダーが有効か調べる
        Collider* objCollider = obj->getColliderPtr();
        if (!objCollider->getEnable())continue;

        //コライダーが衝突していたらディスパッチする
        if (isHitCollider(gameObjectCollider, objCollider)) {
            gameObject->dispatch(obj.get());
            obj->dispatch(gameObject);
        }
    }
}

/**
* @brief リストと1ゲームオブジェクトの衝突を解決する
*/
template<class T, class T2>
void solveCollideBothList(std::vector<T>& list1, std::vector<T2>& list2) {
    for (auto&& obj1 : list1) {
        if (!obj1->getColliderPtr()->getEnable())continue;
        solveCollideObjectToList(obj1.get(), list2);
    }
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

    solveCollideBothList(mBullets, mEnemies);
    solveCollideObjectToList(mPlayer.get(), mEnemies);
    solveCollideObjectToList(mPlayer.get(), mItems);

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

void GameObjectManager::draw(Graphics::IRenderer* renderer) {
    //影の描画時は床を描画したくない
    mField->draw(renderer);
    mPlayer->draw(renderer);
    //for (auto&& bullet : mBullets) {
    //    bullet->draw(renderer);
    //}
    //for (auto&& enemy : mEnemies) {
    //    enemy->draw(renderer);
    //}
    //for (auto&& item : mItems) {
    //    item->draw(renderer);
    //}
}

void GameObjectManager::draw(int phase) {}

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
