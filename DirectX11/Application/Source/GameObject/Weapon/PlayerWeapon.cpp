#include "PlayerWeapon.h"

using namespace Framework;

PlayerWeapon::PlayerWeapon(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :GameObject(transform, mediator) {}

PlayerWeapon::~PlayerWeapon() {}
