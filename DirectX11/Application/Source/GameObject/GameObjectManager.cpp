#include "GameObjectManager.h"
#include "Source/GameObject/Collider.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Source/GameObject/Player.h"
#include "Source/GameObject/Wall.h"

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

    Utility::StringBuilder sb("NoHit\n");
    for (auto&& wall : mWallList) {
        if (mPlayer->getCollider()->getOBB().isCollide(wall->getCollider()->getOBB())) {
            sb = Utility::StringBuilder("Hit");
        }
        Math::OBB3D obb = mPlayer->getCollider()->getOBB();
        sb << "OBB_POS:" << obb.mPosition << "\n";
        sb << "PLAYER_POS:" << mPlayer->getCollider()->transform.get().getGlobalPostition() << "\n";
        sb << "OBB_DIR[0]" << obb.mNormalDirect[0] << "\n";
        sb << "OBB_DIR[1]" << obb.mNormalDirect[1] << "\n";
        sb << "OBB_DIR[2]" << obb.mNormalDirect[2] << "\n";
        sb << "PLAYER_ROT:" << mPlayer->getCollider()->transform.get().getGlobalRotate() << "\n";
        sb << "OBB_SCALE" << obb.mLength << "\n";
        sb << "PLAYER_SCL:" << mPlayer->getCollider()->transform.get().getGlobalScale() << "\n";
        obb = wall->getCollider()->getOBB();
        sb << obb.mPosition << "\n";
        sb << "OBB2_POS:" << obb.mPosition << "\n";
        sb << "WALL_POS:" << wall->getCollider()->transform.get().getGlobalPostition() << "\n";
        sb << "OBB_DIR[0]" << obb.mNormalDirect[0] << "\n";
        sb << "OBB_DIR[1]" << obb.mNormalDirect[1] << "\n";
        sb << "OBB_DIR[2]" << obb.mNormalDirect[2] << "\n";
        sb << "WALL_ROT:" << wall->getCollider()->transform.get().getGlobalRotate() << "\n";
        sb << "OBB_SCALE" << obb.mLength << "\n";
        sb << "WALL_SCL:" << wall->getCollider()->transform.get().getGlobalScale() << "\n";
        mText->setText(sb.getStr());
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
