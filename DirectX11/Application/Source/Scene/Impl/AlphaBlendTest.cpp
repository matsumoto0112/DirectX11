#include "AlphaBlendTest.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/ImGUI/Window.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Utility/ImGUI/FloatField.h"
#include "Source/DefienClearColor.h"
#include "Framework/Utility/ImGUI/Text.h"
#include "Framework/Utility/ImGUI/Button.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"

using namespace Framework;

#define ADD_BACK_COLOR_CHANGE_FIELD(name,type) { \
        std::shared_ptr<ImGUI::FloatField> field = \
            std::make_shared<ImGUI::FloatField>(#name,DefineClearColor::getColor().##type,[&](float val){ \
            Graphics::Color4 col = DefineClearColor::getColor(); \
            col.##type = val; \
            DefineClearColor::setColor(col); \
            }); \
        mUIWindow->addItem(field); \
    }
#define ADD_ALPHABLEND_STATE_CHANGE_FIELD(name,var,val) {\
        std::shared_ptr<ImGUI::Button> btn = \
            std::make_shared<ImGUI::Button>(#name,[&](){ \
                bd.##var = val; \
                updateBlend(); \
            }); \
        mUIWindow->addItem(btn); \
    }
#define ADD_CHANGE_BLEND_STATE_SET(name,func) { \
        std::shared_ptr<ImGUI::Button> btn = \
            std::make_shared<ImGUI::Button>(#name ,[&](){ \
                RenderTarget = func (); \
                updateBlend(); \
            }); \
        mUIWindow->addItem(btn); \
    }
#define ADD_COLOR_CHANGE_FIELD(name,var,type) {\
        std::shared_ptr<ImGUI::FloatField> field = \
            std::make_shared<ImGUI::FloatField>(#name ,var.##type,[&](float val){ \
                var.##type = val; \
            }); \
        mUIWindow->addItem(field); \
    }

namespace {
std::unique_ptr<Graphics::AlphaBlend> mAlphaBlend;
float f;
D3D11_BLEND_DESC bd;
D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;
std::shared_ptr<ImGUI::Text> mCurrentText;
Utility::Transform mObj1, mObj2;
Graphics::Color4 mObj1Color, mObj2Color;
}

AlphaBlendTest::AlphaBlendTest()
    :mPerspectiveCamera(std::make_unique<Graphics::PerspectiveCamera>(
        Graphics::PerspectiveCamera::Info{
        Math::Vector3(0,0,-10),
        Math::Vector3(0,0,0),
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,
        1000.0f
        })) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Cube, Define::ModelName::CUBE);
    mEnemy.mModel = fbx->getResource(Define::ModelType::Cube);
    mEnemy.mModel->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Diffuse));
    mObj1 = Utility::Transform(
        Math::Vector3::ZERO,
        Math::Quaternion::IDENTITY,
        Math::Vector3(1, 1, 1)
    );
    mObj2 = Utility::Transform(
        Math::Vector3(3, 0, 5),
        Math::Quaternion::IDENTITY,
        Math::Vector3(1, 1, 1)
    );
    f = 0.0f;

    ZeroMemory(&bd, sizeof(bd));
    ZeroMemory(&RenderTarget, sizeof(RenderTarget));
    bd.AlphaToCoverageEnable = FALSE;
    bd.IndependentBlendEnable = FALSE;
    RenderTarget.BlendEnable = TRUE;
    RenderTarget.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
    RenderTarget.DestBlend = D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
    RenderTarget.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    bd.RenderTarget[0] = RenderTarget;

    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(bd);

    mObj1Color = Graphics::Color4::WHITE;
    mObj2Color = Graphics::Color4::WHITE;

    mUIWindow = std::make_unique<ImGUI::Window>("Changable Area");

    mCurrentText = std::make_shared<ImGUI::Text>("");
    mUIWindow->addItem(mCurrentText);

    auto updateBlend = [&]() {
        bd.RenderTarget[0] = RenderTarget;
        mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(bd);
    };

    ADD_BACK_COLOR_CHANGE_FIELD(R, r);
    ADD_BACK_COLOR_CHANGE_FIELD(G, g);
    ADD_BACK_COLOR_CHANGE_FIELD(B, b);
    ADD_BACK_COLOR_CHANGE_FIELD(A, a);

    ADD_ALPHABLEND_STATE_CHANGE_FIELD(AlphaToCoverageEnable, AlphaToCoverageEnable, TRUE);
    ADD_ALPHABLEND_STATE_CHANGE_FIELD(NonAlphaToCoverageEnable, AlphaToCoverageEnable, FALSE);

    ADD_CHANGE_BLEND_STATE_SET(Default, Graphics::AlphaBlendSetting::getDefaultDesc);
    ADD_CHANGE_BLEND_STATE_SET(Align, Graphics::AlphaBlendSetting::getAlignmentBlendDesc);
    ADD_CHANGE_BLEND_STATE_SET(Add, Graphics::AlphaBlendSetting::getAddBlendDesc);
    ADD_CHANGE_BLEND_STATE_SET(Subtract, Graphics::AlphaBlendSetting::getSubtractBlendDesc);
    ADD_CHANGE_BLEND_STATE_SET(Multiply, Graphics::AlphaBlendSetting::getMultipleBlendDesc);

    ADD_COLOR_CHANGE_FIELD((object 1 color R), mObj1Color, r);
    ADD_COLOR_CHANGE_FIELD((object 1 color G), mObj1Color, g);
    ADD_COLOR_CHANGE_FIELD((object 1 color B), mObj1Color, b);
    ADD_COLOR_CHANGE_FIELD((object 1 color A), mObj1Color, a);

    ADD_COLOR_CHANGE_FIELD((object 2 color R), mObj2Color, r);
    ADD_COLOR_CHANGE_FIELD((object 2 color G), mObj2Color, g);
    ADD_COLOR_CHANGE_FIELD((object 2 color B), mObj2Color, b);
    ADD_COLOR_CHANGE_FIELD((object 2 color A), mObj2Color, a);

}

AlphaBlendTest::~AlphaBlendTest() {}

void AlphaBlendTest::load(Scene::Collecter& collecter) {}

void AlphaBlendTest::update(float delta) {
    f += 1.0f;
    Math::Quaternion rot = Math::Quaternion::createRotateAboutZ(f * 2.5) * Math::Quaternion::createRotateAboutY(f);
    mObj1.setRotate(rot);

    rot = Math::Quaternion::createRotateAboutZ(-f * 2.5) * Math::Quaternion::createRotateAboutY(-f);
    mObj2.setRotate(rot);
}

bool AlphaBlendTest::isEndScene() const {
    return false;
}

void AlphaBlendTest::draw() {
    mAlphaBlend->set();
    {
        Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, mObj1Color);
        mPerspectiveCamera->setMatrix();
        mEnemy.mTransform = mObj1;
        mEnemy.draw();
    }

    {
        Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, mObj2Color);
        mEnemy.mTransform = mObj2;
        mEnemy.draw();
    }

    {
        Utility::StringBuilder sb("");
        Graphics::Color4 col = DefineClearColor::getColor();
        sb << "(" << col.r << "," << col.g << "," << col.b << "," << col.a << ")\n";
        sb << RenderTarget.BlendEnable << "\n";
        mCurrentText->setText(sb.getStr());
    }
    mUIWindow->draw();
}

void AlphaBlendTest::end() {}

Define::SceneType AlphaBlendTest::next() {
    return Define::SceneType();
}

void AlphaBlendTest::GameObject::draw() {
    mModel->draw(mTransform);
}