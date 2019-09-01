#include "Source/Scene/Impl/Main.h"
#include "Source/GameObject/GameObjectManager.h"

using namespace Framework;

Main::Main() {
    std::unique_ptr<GameObject> player = std::make_unique<GameObject>(Utility::Transform());
    mManager = std::make_unique<GameObjectManager>(std::move(player));
}

Main::~Main() {}

void Main::load(Scene::Collecter& collecter) {}

void Main::update() {
    mManager->update();
}

bool Main::isEndScene() const {
    return false;
}

void Main::draw() {
    mManager->draw();
}

void Main::end() {}

Define::SceneType Main::next() {
    return Define::SceneType();
}
