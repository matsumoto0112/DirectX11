#include "Title.h"
#include "Define/Window.h"
#include "Graphics/String/TextureString.h"
#include "Scene/Collecter.h"
#include "Source/Scene/Data/TitleData.h"
#include "Utility/Wrap/OftenUsed.h"

using namespace Framework;

Title::Title()
    :mTitleStr(std::make_unique<Graphics::TextureString>("Title", 140, "")) {
    mTitleStr->setPosition(Math::Vector2(0, 0));
}

Title::~Title() {}

void Title::load(Scene::Collecter& collecter) {}

void Title::update(float delta) {}

bool Title::isEndScene() const {
    return false;
}

void Title::draw() {
    Math::Matrix4x4 proj = Math::Matrix4x4::createOrthographic(Define::Window::getSize());
    Math::Matrix4x4 view = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::Projection, proj);
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::View, view);

    mTitleStr->draw();
}

void Title::end() {}

Define::SceneType Title::next() {
    return Define::SceneType::MainPlay;
}
