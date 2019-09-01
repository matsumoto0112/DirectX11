#include "Wall.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/ImGUI/Window.h"
#include "Framework/Utility/ImGUI/FloatField.h"
#include "Framework/Utility/Debug.h"

using namespace Framework;
namespace {
std::unique_ptr<ImGUI::Window> mUIWindow;
}

Wall::Wall(const Utility::Transform& transform)
    : GameObject(transform) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    mModel = fbx->getResource(Define::ModelType::Wall);
    mModel->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Diffuse));

    mUIWindow = std::make_unique<ImGUI::Window>("Object Field");

#define ADD_WALL_POSITION_CHANGE_FIELD(name,type) { \
    std::shared_ptr<ImGUI::FloatField> field = \
        std::make_shared<ImGUI::FloatField>(#name, mTransform.getPosition().##type, [&](float val) { \
        Math::Vector3 pos = mTransform.getPosition(); \
        pos.##type = val; \
        mTransform.setPosition(pos); \
    }); \
    field ->setMinValue(-50.0f); \
    field->setMaxValue(50.0f); \
    mUIWindow->addItem(field); \
    }

#define ADD_WALL_ROTATE_CHANGE_FIELD(name,type) { \
    std::shared_ptr<ImGUI::FloatField> field = \
        std::make_shared<ImGUI::FloatField>(#name, mTransform.getRotate().toEular().##type, [&](float val) { \
        Math::Quaternion rot = mTransform.getRotate(); \
        Math::Vector3 eular = rot.toEular(); \
        eular.##type = val; \
        rot = Math::Quaternion::fromEular(eular); \
        mTransform.setRotate(rot); \
    }); \
    field ->setMinValue(-180.0f); \
    field->setMaxValue(180.0f); \
    mUIWindow->addItem(field); \
    }

    ADD_WALL_POSITION_CHANGE_FIELD(X, x);
    ADD_WALL_POSITION_CHANGE_FIELD(Y, y);
    ADD_WALL_POSITION_CHANGE_FIELD(Z, z);

    ADD_WALL_ROTATE_CHANGE_FIELD(RX, x);
    ADD_WALL_ROTATE_CHANGE_FIELD(RY, y);
    ADD_WALL_ROTATE_CHANGE_FIELD(RZ, z);
}

Wall::~Wall() {}

void Wall::update() {
    //Math::Quaternion rot = mTransform.getRotate();
    //rot = rot * Math::Quaternion::createRotateAboutY(1);
    //mTransform.setRotate(rot);
    //MY_DEBUG_LOG(Utility::StringBuilder("") << mTransform.getRotate().toEular().y);
}

void Wall::draw() {
    mModel->draw(mTransform);

    mUIWindow->draw();
}
