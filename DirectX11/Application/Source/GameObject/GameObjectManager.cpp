#include "GameObjectManager.h"
#include <algorithm>

GameObjectManager::GameObjectManager(GameObjectPtr player) {}

GameObjectManager::~GameObjectManager() {}

void GameObjectManager::update() {
    mPlayer->update();
}

void GameObjectManager::draw() {
    mPlayer->draw();
}
