#include "Player.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Framework/Define/Window.h"
#include "Framework/Utility/Debug.h"

using namespace Framework;

namespace {
Math::Vector3 calc(const Math::Vector3& mouse,
    const Math::Matrix4x4& invView,
    const Math::Matrix4x4& invProj,
    const Math::Matrix4x4& invVP) {
    Math::Matrix4x4 tmp = invVP * invProj * invView;
    Math::Matrix4x4 pos = Math::Matrix4x4::createTranslate(mouse);
    Math::Matrix4x4 m = pos * tmp;
    Math::Vector3 res(m.m[3][0] / m.m[3][3], m.m[3][1] / m.m[3][3], m.m[3][2] / m.m[3][3]);
    return res;
}

Math::Vector3 getPos(IMainSceneMediator& mediator) {
    Math::Vector2 mousePositon = Utility::getInputManager()->getMouse().getMousePosition();
    Math::Matrix4x4 view = mediator.getMainCamera()->getView();
    Math::Matrix4x4 proj = mediator.getMainCamera()->getProjection();
    float x = Define::Window::WIDTH / 2;
    float y = Define::Window::HEIGHT / 2;
    Math::Matrix4x4 viewport = Math::Matrix4x4(
        x, 0, 0, 0,
        0, -y, 0, 0,
        0, 0, 1, 0,
        x, y, 0, 1
    );

    view = Math::Matrix4x4::inverse(view);
    proj = Math::Matrix4x4::inverse(proj);
    viewport = Math::Matrix4x4::inverse(viewport);

    Math::Vector3 nearPos = calc(Math::Vector3(mousePositon.x, mousePositon.y, 0.0f),
        view, proj, viewport);
    Math::Vector3 farPos = calc(Math::Vector3(mousePositon.x, mousePositon.y, 1.0f),
        view, proj, viewport);
    Math::Vector3 ray = farPos - nearPos;
    ray.normalize();

    if (ray.y <= 0) {
        float lRay = Math::Vector3::dot(ray, Math::Vector3::UP);
        float lp0 = Math::Vector3::dot(-nearPos, Math::Vector3::UP);
        return nearPos + (lp0 / lRay) * ray;
    }
    return Math::Vector3::ZERO;
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

    Math::Vector3 pos = getPos(mMediator);
    Math::Vector3 playerPosition = mTransform.getPosition();

    Math::Vector3 z = (pos - playerPosition).getNormal();
    Math::Vector3 x = Math::Vector3::cross(Math::Vector3::UP, z).getNormal();
    Math::Vector3 y = Math::Vector3::cross(z, x).getNormal();

    Math::Matrix4x4 mat = Math::Matrix4x4(
        x.x, x.y, x.z, 0,
        y.x, y.y, y.z, 0,
        z.x, z.y, z.z, 0,
        0, 0, 0, 1
    );

    Math::Quaternion rot = mat.toQuaternion();
    mTransform.setRotate(rot);
}
