#include "Collidable3DObject.h"

Collidable3DObject::Collidable3DObject(const Framework::Utility::Transform& transform,
    IMainSceneMediator& mediator, Define::ModelType modelType, std::unique_ptr<Collider> collider)
    :GameObject3D(transform, mediator, modelType), mIsAlive(true), mCollider(std::move(collider)) {}

Collidable3DObject::~Collidable3DObject() {}

void Collidable3DObject::draw() {
    GameObject3D::draw();
    mCollider->render();
}

