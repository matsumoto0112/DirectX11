#include "Floor.h"

using namespace Framework;

Floor::Floor(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :GameObject3D(transform, mediator, Define::ModelType::Plane) {}

Floor::~Floor() {}
