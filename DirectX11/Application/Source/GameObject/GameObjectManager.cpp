#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(GameObjectPtr player, GameObjectPtr floor)
    :mPlayer(std::move(player)), mFloor(std::move(floor)) {}

GameObjectManager::~GameObjectManager() {}

void GameObjectManager::update() {
    mPlayer->update();
}

void GameObjectManager::draw() {
    mFloor->draw();
    mPlayer->draw();
    for (auto&& wall : mWallList) {
        wall->draw();
    }
}

void GameObjectManager::addWall(GameObjectPtr wall) {
    mWallList.emplace_back(std::move(wall));
}
