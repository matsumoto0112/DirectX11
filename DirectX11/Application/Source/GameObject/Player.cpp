#include "Player.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Framework/Define/Window.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Collision.h"

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

//マウスの方向を向くクォータニオンを計算する
Math::Quaternion calcMouseLookat(const Math::Vector3& player, const Graphics::PerspectiveCamera* camera) {
    Math::Vector3 pos = getMousePlanePosition(Utility::getInputManager()->getMouse().getMousePosition(), camera);

    Math::Vector3 z = (pos - player).getNormal();
    Math::Vector3 x = Math::Vector3::cross(Math::Vector3::UP, z).getNormal();
    Math::Vector3 y = Math::Vector3::cross(z, x).getNormal();

    Math::Matrix4x4 mat = Math::Matrix4x4(
        x.x, x.y, x.z, 0,
        y.x, y.y, y.z, 0,
        z.x, z.y, z.z, 0,
        0, 0, 0, 1
    );

    Math::Quaternion rot = mat.toQuaternion();
    return rot;
}
}

Player::Player(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :GameObject3D(transform, Define::ModelType::Player),
    mMediator(mediator),
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

    mTransform.setRotate(calcMouseLookat(mTransform.getPosition(), mMediator.getMainCamera()));
}
