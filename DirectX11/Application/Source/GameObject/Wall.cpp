#include "Wall.h"
#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/GameObject/IMainSceneMediator.h"

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


Wall::Wall(const Utility::Transform& transform, IMainSceneMediator& mMediator)
    : GameObject3D(transform, Define::ModelType::Wall) {
    mCube = std::make_unique<Graphics::Cube>();
    std::unique_ptr<ImGUI::Window> window = std::make_unique<ImGUI::Window>("WallCollision");
    mCubeTransform = Utility::Transform(
        Math::Vector3(0, 0.0f, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(10.0f, 5.0f, 1.0f)
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

Wall::~Wall() {}

void Wall::draw() {
    GameObject3D::draw();

    Graphics::Color4 color = Graphics::Color4(1.0f, 0.0f, 0.0f, 0.2f);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
    Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Only_Position)->set();
    Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::OutPot_Color)->set();
    mCube->render(mCubeTransform);
    color = Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
}
