#include "GameObjectManager.h"
#include "Framework/Utility/Collision.h"
#include "Source/GameObject/Collider.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Source/GameObject/Player.h"
#include "Source/GameObject/Field.h"

using namespace Framework;

namespace {
std::shared_ptr<ImGUI::Text> mText;
}

GameObjectManager::GameObjectManager(IMainSceneMediator & mediator, std::unique_ptr<Player> player, std::unique_ptr<Field> field)
    :mMediator(mediator), mPlayer(std::move(player)), mField(std::move(field)) {
    std::shared_ptr<ImGUI::Window> window = std::make_shared<ImGUI::Window>("Collision");
    mText = std::make_shared<ImGUI::Text>("Hit");
    window->addItem(mText);
    mMediator.addDebugUI(window);
}

GameObjectManager::~GameObjectManager() {
    mBullets.clear();
}

void GameObjectManager::update() {
    mPlayer->update();
    for (auto&& bullet : mBullets) {
        bullet->update();
    }
    for (auto&& enemy : mEnemy) {
        enemy->update();
    }

    mField->pushBackGameObject(*mPlayer);
}

void GameObjectManager::draw() {
    mField->draw();
    mPlayer->draw();
    for (auto&& bullet : mBullets) {
        bullet->draw();
    }
    for (auto&& enemy : mEnemy) {
        enemy->draw();
    }
}

void GameObjectManager::addBullet(GameObjectPtr bullet) {
    mBullets.emplace_back(std::move(bullet));
}

void GameObjectManager::addEnemy(GameObjectPtr enemy) {
    mEnemy.emplace_back(std::move(enemy));
}