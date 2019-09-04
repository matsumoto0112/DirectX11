#include "Wall.h"
#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Source/GameObject/Collider.h"

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


Wall::Wall(const Utility::Transform& transform, IMainSceneMediator& mediator)
    : GameObject3D(transform, mediator, Define::ModelType::Wall) {
    Utility::Transform tr = Utility::Transform(
        Math::Vector3(0, 0.0f, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(10.0f, 5.0f, 1.0f)
    );
    tr.setParent(&mTransform);
    mCollider = std::make_unique<Collider>(tr);
}

Wall::~Wall() {}

void Wall::draw() {
    GameObject3D::draw();
    mCollider->render();
}
