#include "Collidable3DObject.h"

Collidable3DObject::Collidable3DObject(const Framework::Utility::Transform& transform,
    IMainSceneMediator& mediator, Define::ModelType modelType, std::unique_ptr<Collider> collider)
    :GameObject3D(transform, mediator, modelType), mCollider(std::move(collider)) {}

Collidable3DObject::~Collidable3DObject() {}
