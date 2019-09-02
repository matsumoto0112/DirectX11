#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(GameObjectPtr player, GameObjectPtr floor)
    :mPlayer(std::move(player)), mFloor(std::move(floor)) {}

GameObjectManager::~GameObjectManager() {
    mWallList.clear();
    mBullets.clear();
}

void GameObjectManager::update() {
    mPlayer->update();
    for (auto&& bullet : mBullets) {
        bullet->update();
    }
}

void GameObjectManager::draw() {
    mFloor->draw();
    mPlayer->draw();
    for (auto&& bullet : mBullets) {
        bullet->draw();
    }

    for (auto&& wall : mWallList) {
        wall->draw();
    }
}

void GameObjectManager::addWall(GameObjectPtr wall) {
    mWallList.emplace_back(std::move(wall));
}

void GameObjectManager::addBullet(GameObjectPtr bullet) {
    mBullets.emplace_back(std::move(bullet));
}
