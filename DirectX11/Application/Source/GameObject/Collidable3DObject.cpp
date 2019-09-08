#include "Collidable3DObject.h"

Collidable3DObject::Collidable3DObject(const Framework::Utility::Transform& transform,
    IMainSceneMediator& mediator, Define::ModelType modelType)
    :GameObject3D(transform, mediator, modelType), mIsAlive(true), mCollider(nullptr) {}

Collidable3DObject::~Collidable3DObject() {}

void Collidable3DObject::initialize() {
    mCollider = createCollider();
}

void Collidable3DObject::draw() {
    GameObject3D::draw();
    mCollider->render();
}

