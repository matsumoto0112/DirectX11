#include "Player.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Graphics/Model/Model.h"

using namespace Framework;

Player::Player(const Utility::Transform& transform)
    :GameObject3D(transform, Define::ModelType::Player),
    mMoveSpeed(10.0f) {}

Player::~Player() {}

void Player::update() {
    const Input::Keyboard& key = Utility::getInputManager()->getKeyboard();
    Math::Vector3 movement = Math::Vector3::ZERO;
    if (key.getKey(Input::KeyCode::Left)) {
        movement.x--;
    }
    if (key.getKey(Input::KeyCode::Right)) {
        movement.x++;
    }
    if (key.getKey(Input::KeyCode::Up)) {
        movement.z++;
    }
    if (key.getKey(Input::KeyCode::Down)) {
        movement.z--;
    }
    movement.normalize();

    mTransform.setPosition(mTransform.getPosition() + movement * mMoveSpeed *  Utility::Time::getInstance().DeltaTime);
}
