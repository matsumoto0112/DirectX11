#include "GameObjectManager.h"
#include <algorithm>

GameObjectManager::GameObjectManager(GameObjectPtr player)
    :mPlayer(std::move(player)) {}

GameObjectManager::~GameObjectManager() {}

void GameObjectManager::update() {
    mPlayer->update();
    for (auto&& wall : mWallList) {
        wall->update();
    }

}

void GameObjectManager::draw() {
    mPlayer->draw();
    for (auto&& wall : mWallList) {
        wall->draw();
    }
}

void GameObjectManager::addWall(GameObjectPtr wall) {
    mWallList.emplace_back(std::move(wall));
}
