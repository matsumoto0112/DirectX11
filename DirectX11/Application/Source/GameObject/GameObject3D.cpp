#include "GameObject3D.h"
#include "Framework/Utility/Resource/ResourceManager.h"
using namespace Framework;

GameObject3D::GameObject3D(const Utility::Transform& transform, IMainSceneMediator& mediator, Define::ModelType modelType)
    :GameObject(transform, mediator) {
    if (modelType == Define::ModelType::NONE) return;
    mModel = Utility::ResourceManager::getInstance().getFBXModel()->getResource(modelType);
}

GameObject3D::~GameObject3D() {}

void GameObject3D::draw() {
    mModel->draw(mTransform);
}
