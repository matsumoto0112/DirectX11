#pragma once
#include <vector>
#include <memory>
#include "Framework/Scene/SceneBase.h"
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {
class DirectionalLight;
class PointLight;
class Model;
class OrthographicCamera;
class PerspectiveCamera;
class TextureString;
} //Graphics
namespace ImGUI {
class Window;
} //ImGUI 
} //Framework 

struct GameObject {
    Framework::Utility::Transform mTransform;
    std::shared_ptr<Framework::Graphics::Model> mModel;
    void draw();
};

/**
* @class NormalLightingTest
* @brief 通常ライトテストシーン
*/
class NormalLightingTest : public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    NormalLightingTest();
    /**
    * @brief デストラクタ
    */
    ~NormalLightingTest();
    virtual void load(Framework::Scene::Collecter& collecter) override;

    virtual void update() override;

    virtual bool isEndScene() const override;

    virtual void draw() override;

    virtual void end() override;

    virtual Define::SceneType next() override;
private:
    std::vector<Framework::Utility::Transform> mWallTransforms;
    std::shared_ptr<Framework::Graphics::Model> mWall;
    GameObject mObject;
    GameObject mFloor;
    std::unique_ptr<Framework::Graphics::TextureString> mStr;
    std::unique_ptr<Framework::Graphics::PerspectiveCamera> mPerspectiveCamera;
    std::unique_ptr<Framework::Graphics::OrthographicCamera> mOrthographicCamera;
    std::shared_ptr<Framework::Graphics::DirectionalLight> mDirectionalLight;
    std::shared_ptr<Framework::Graphics::PointLight> mPointLight;

    std::unique_ptr<Framework::ImGUI::Window> mUIWindow;
};