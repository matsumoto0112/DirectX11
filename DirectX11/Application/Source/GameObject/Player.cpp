#include "Player.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Framework/Define/Window.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Collision.h"
#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Source/GameObject/Collider.h"

using namespace Framework;

namespace {
//マウスの座標を平面上の座標に変換する
Math::Vector3 getMousePlanePosition(const Math::Vector2& mouse, const Graphics::PerspectiveCamera* camera) {
    Math::Vector3 nearPos = camera->screenToWorldPosition(mouse, 0.0f);
    Math::Vector3 farPos = camera->screenToWorldPosition(mouse, 1.0f);
    Math::Vector3 pos;
    if (!Utility::Collision::line_plane(Math::Line(nearPos, farPos), Math::Plane(Math::Vector3(0, 0, 0), Math::Vector3::UP), &pos)) {
        pos = farPos;
    }
    return pos;
}

}

Player::Player(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :GameObject3D(transform, mediator, Define::ModelType::Player),
    mMediator(mediator),
    mMoveSpeed(10.0f) {
    mTransform.setRotate(Math::Quaternion::createRotateAboutY(-90.0f));
    Utility::Transform colliderTransform = Utility::Transform(
        Math::Vector3(0, 0.6f, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(0.6f, 1.5f, 0.8f));
    //Utility::Transform colliderTransform = Utility::Transform(
    //    Math::Vector3(0, 0, 0),
    //    Math::Quaternion::IDENTITY,
    //    Math::Vector3(1, 1, 1));
    colliderTransform.setParent(&mTransform);

    mCollider = std::make_unique<Collider>(colliderTransform);
}

Player::~Player() {}

void Player::update() {
    const Input::Keyboard& key = Utility::getInputManager()->getKeyboard();
    Math::Vector3 movement = Math::Vector3::ZERO;
    if (key.getKey(Input::KeyCode::A)) {
        movement.x--;
    }
    if (key.getKey(Input::KeyCode::D)) {
        movement.x++;
    }
    if (key.getKey(Input::KeyCode::W)) {
        movement.z++;
    }
    if (key.getKey(Input::KeyCode::S)) {
        movement.z--;
    }
    movement.normalize();

    mTransform.setPosition(mTransform.getPosition() + movement * mMoveSpeed *  Utility::Time::getInstance().DeltaTime);

    mTransform.lookat(getMousePlanePosition(Utility::getInputManager()->getMouse().getMousePosition(), mMediator.getMainCamera()));

    if (Utility::getInputManager()->getMouse().getMouseDown(Input::MouseButton::Left)) {
        //Utility::Transform bullet = mTransform;
        //bullet.setPosition(bullet.getPosition() + Math::Vector3(0, 1.10f, 0));
        //mMediator.shotBullet(bullet);
    }
}

void Player::draw() {
    GameObject3D::draw();
    mCollider->render();
}

Collider* Player::getCollider() const {
    return mCollider.get();
}
