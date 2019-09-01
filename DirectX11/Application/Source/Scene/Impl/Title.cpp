#include "Title.h"
#include "Framework/Graphics/String/TextureString.h"
#include "Framework/Scene/Collecter.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/Scene/Data/TitleData.h"
#include "Framework/Define/Window.h"

using namespace Framework;

Title::Title()
    :mTitleStr(std::make_unique<Graphics::TextureString>("Title", 140, "")) {
    mTitleStr->setPosition(Math::Vector2(50, 0));
}

Title::~Title() {}

void Title::load(Framework::Scene::Collecter& collecter) {}

void Title::update() {}

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
