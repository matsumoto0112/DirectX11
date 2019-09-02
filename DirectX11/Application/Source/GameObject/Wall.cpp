#include "Wall.h"
#include "Framework/Utility/Resource/ResourceManager.h"

using namespace Framework;

Wall::Wall(const Utility::Transform& transform)
    : GameObject(transform) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    mModel = fbx->getResource(Define::ModelType::Wall);
    mModel->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Diffuse));
}

Wall::~Wall() {}

void Wall::update() {}

void Wall::draw() {
    mModel->draw(mTransform);
}
