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
#include "Source/GameObject/Weapon/SingleShotWeapon.h"

using namespace Framework;

namespace {
constexpr int MAX_HP = 100;
constexpr int DAMAGE = 20;

std::shared_ptr<ImGUI::FloatField> mHP;
//マウスの座標を平面上の座標に変換する
Math::Vector3 getMousePlanePosition(const Math::Vector2& mouse, const FollowCamera* camera) {
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
    :Collidable3DObject(transform, mediator, Define::ModelType::Player),
    mMoveSpeed(10.0f),
    mWeapon(nullptr) {
    Utility::Transform tr = mTransform;
    tr.setPosition(tr.getPosition() + Math::Vector3(0, 1.1f, 0.0f));
    tr.setParent(&mTransform);
    mWeapon = std::make_unique<SingleShotWeapon>(tr, mMediator);
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

    mTransform.setPosition(mTransform.getPosition() + movement * mMoveSpeed *  Utility::Time::getInstance().getDeltaTime());

    mTransform.lookat(getMousePlanePosition(Utility::getInputManager()->getMouse().getMousePosition(), mMediator.getMainCamera()));

    if (Utility::getInputManager()->getMouse().getMouse(Input::MouseButton::Left)) {
        mWeapon->pullTrigger();
    }
}

void Player::dispatch(Collidable3DObject* other) {
    other->hit(this);
}

void Player::hit(Enemy* other) {}

std::unique_ptr<Collider> Player::createCollider() {
    Utility::Transform colliderTransform = Utility::Transform(
        Math::Vector3(0, 0.6f, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(0.6f, 1.5f, 0.8f));
    colliderTransform.setParent(&mTransform);
    return std::make_unique<Collider>(colliderTransform, this);
}

