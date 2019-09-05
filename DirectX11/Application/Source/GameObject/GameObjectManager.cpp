#include "GameObjectManager.h"
#include "Source/GameObject/Collider.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Source/GameObject/Player.h"
#include "Source/GameObject/Wall.h"
#include "Framework/Utility/Collision.h"

using namespace Framework;

namespace {
std::shared_ptr<ImGUI::Text> mText;
}

GameObjectManager::GameObjectManager(IMainSceneMediator & mediator, std::unique_ptr<Player> player, GameObjectPtr floor)
    :mMediator(mediator), mPlayer(std::move(player)), mFloor(std::move(floor)) {
    std::shared_ptr<ImGUI::Window> window = std::make_shared<ImGUI::Window>("Collision");
    mText = std::make_shared<ImGUI::Text>("Hit");
    window->addItem(mText);
    mMediator.addDebugUI(window);
}

GameObjectManager::~GameObjectManager() {
    mWallList.clear();
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

    Math::Plane px(Math::Vector3(-5.0f, 0, 0), Math::Vector3::RIGHT);
    float len = 0.0f;
    if (Utility::Collision::obb_plane(mPlayer->getCollider()->getOBB(), px, &len)) {
        Math::Vector3 pos = mPlayer->getTransform().getPosition();
        pos.x += len;
        mPlayer->getTransformPtr()->setPosition(pos);
    }
}

void GameObjectManager::draw() {
    mFloor->draw();
    mPlayer->draw();
    for (auto&& bullet : mBullets) {
        bullet->draw();
    }


    for (auto&& enemy : mEnemy) {
        enemy->draw();
    }

    for (auto&& wall : mWallList) {
        wall->draw();
    }
}

void GameObjectManager::addWall(std::unique_ptr<Wall> wall) {
    mWallList.emplace_back(std::move(wall));
}

void GameObjectManager::addBullet(GameObjectPtr bullet) {
    mBullets.emplace_back(std::move(bullet));
}

void GameObjectManager::addEnemy(GameObjectPtr enemy) {
    mEnemy.emplace_back(std::move(enemy));
}
