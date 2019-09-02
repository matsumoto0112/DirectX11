#include "Floor.h"

using namespace Framework;

Floor::Floor(const Utility::Transform& transform)
    :GameObject3D(transform, Define::ModelType::Plane) {}

Floor::~Floor() {}
