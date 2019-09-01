#include "Player.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Graphics/Model/Model.h"

using namespace Framework;

Player::Player(const Utility::Transform& transform)
    :GameObject(transform),
    mMoveSpeed(10.f) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    mModel = fbx->getResource(Define::ModelType::Player);
    mModel->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Diffuse));
}

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

void Player::draw() {
    mModel->draw(mTransform);
}
