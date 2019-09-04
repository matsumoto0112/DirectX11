#include "Enemy.h"

using namespace Framework;
Enemy::Enemy(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :GameObject3D(transform, mediator, Define::ModelType::Enemy) {}

Enemy::~Enemy() {}
