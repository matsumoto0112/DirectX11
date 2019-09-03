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

using namespace Framework;
#define ADD_POSITION_CHANGE_FIELD(name,type) {\
    float def = mCubeTransform.getPosition().##type; \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name, def, [&](float val) { \
        Math::Vector3 pos = mCubeTransform.getPosition(); \
        pos.##type = val; \
        mCubeTransform.setPosition(pos); \
    }); \
    field->setMinValue(-10.0f); \
    field->setMaxValue(10.0f); \
    window->addItem(field); \
}
#define ADD_SCALE_CHANGE_FIELD(name,type) {\
    float def = mCubeTransform.getScale().##type; \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name, def, [&](float val) { \
        Math::Vector3 scale = mCubeTransform.getScale(); \
        scale.##type = val; \
        mCubeTransform.setScale(scale); \
    }); \
    field->setMinValue(-10.0f); \
    field->setMaxValue(10.0f); \
    window->addItem(field); \
}


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
    :GameObject3D(transform, Define::ModelType::Player),
    mMediator(mediator),
    mMoveSpeed(10.0f) {
    mCube = std::make_unique<Graphics::Cube>();

    std::unique_ptr<ImGUI::Window> window = std::make_unique<ImGUI::Window>("PlayerCollision");
    mCubeTransform = Utility::Transform(
        Math::Vector3(0, 0.6f, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(0.6f, 1.5f, 0.8f)
    );
    mCubeTransform.setParent(&mTransform);

    ADD_POSITION_CHANGE_FIELD(Pos_X, x);
    ADD_POSITION_CHANGE_FIELD(Pos_Y, y);
    ADD_POSITION_CHANGE_FIELD(Pos_Z, z);

    ADD_SCALE_CHANGE_FIELD(Scale_X, x);
    ADD_SCALE_CHANGE_FIELD(Scale_Y, y);
    ADD_SCALE_CHANGE_FIELD(Scale_Z, z);

    mMediator.addDebugUI(std::move(window));
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

    //mTransform.lookat(getMousePlanePosition(Utility::getInputManager()->getMouse().getMousePosition(), mMediator.getMainCamera()));

    if (Utility::getInputManager()->getMouse().getMouseDown(Input::MouseButton::Left)) {
        Utility::Transform bullet = mTransform;
        bullet.setPosition(bullet.getPosition() + Math::Vector3(0, 1.10f, 0));
        mMediator.shotBullet(bullet);
    }
}

void Player::draw() {
    GameObject3D::draw();

    Graphics::Color4 color = Graphics::Color4(1.0f, 0.0f, 0.0f, 0.2f);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
    Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Only_Position)->set();
    Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::OutPot_Color)->set();
    mCube->render(mCubeTransform);
    color = Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);

}
