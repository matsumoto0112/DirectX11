#include "Manager.h"
#include "Framework/Scene/Collecter.h"
#include "Framework/Scene/SceneBase.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Scene {

Manager::Manager()
    :mCollecter(std::make_unique<Collecter>()) {}

Manager::~Manager() {}

void Manager::update() {
    MY_ASSERTION(mCurrentScene, "�V�[�������݂��܂���");
    mCurrentScene->update();
    if (mCurrentScene->isEndScene()) {
        loadScene(mCurrentScene->next());
    }
}

void Manager::draw(Graphics::Pipeline* pipeline) {
    MY_ASSERTION(mCurrentScene, "�V�[�������݂��܂���");
    mCurrentScene->draw(pipeline);
}

void Manager::registerScene(Define::SceneType type, ScenePtr scene) {
    MY_DEBUG_LOG_IF(mCreatedScene.find(type) != mCreatedScene.end(), "�o�^�ς݂̃V�[�����ēo�^����܂���");
    mCreatedScene[type] = std::move(scene);
}

void Manager::loadScene(Define::SceneType next) {
    if (mCurrentScene)mCurrentScene->end();
    mCurrentScene = getNextScene(next);
    mCurrentScene->load(*mCollecter);
}

SceneBase* Manager::getNextScene(Define::SceneType next) {
    MY_ASSERTION(mCreatedScene.find(next) != mCreatedScene.end(), "���o�^�̃V�[�����Ă΂�܂���");
    return mCreatedScene[next].get();
}

} //Scene 
} //Framework 

