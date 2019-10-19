#include "TestScene.h"

using namespace Framework;

TestScene::TestScene() { }

TestScene::~TestScene() { }

void TestScene::load(Scene::Collecter& collecter) { }

void TestScene::update() { }

bool TestScene::isEndScene() const {
    return false;
}

void TestScene::draw(Graphics::IRenderer * renderer) { }

void TestScene::unload() { }

Define::SceneType TestScene::next() {
    return Define::SceneType();
}
