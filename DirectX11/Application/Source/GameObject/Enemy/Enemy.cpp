#include "Enemy.h"

using namespace Framework;
Enemy::Enemy(const Utility::Transform& transform)
    :GameObject3D(transform, Define::ModelType::Enemy) {}

Enemy::~Enemy() {}
