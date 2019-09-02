#include "Wall.h"

using namespace Framework;

Wall::Wall(const Utility::Transform& transform)
    : GameObject3D(transform, Define::ModelType::Wall) {}

Wall::~Wall() {}
