#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {
class Model;
class PerspectiveCamera;
} //Graphics
namespace ImGUI {
class Window;
} //ImGUI 
} //Framework 

/**
* @class AlphaBlendTest
* @brief アルファブレンドテストシーン
*/
class AlphaBlendTest : public Framework::Scene::SceneBase {
    struct GameObject {
        Framework::Utility::Transform mTransform;
        std::shared_ptr<Framework::Graphics::Model> mModel;
        void draw();
    };
public:
    /**
    * @brief コンストラクタ
    */
    AlphaBlendTest();
    /**
    * @brief デストラクタ
    */
    ~AlphaBlendTest();
    virtual void load(Framework::Scene::Collecter& collecter) override;
    virtual void update(float delta) override;
    virtual bool isEndScene() const override;
    virtual void draw() override;
    virtual void end() override;
    virtual Define::SceneType next() override;
private:
    GameObject mEnemy;
    std::unique_ptr<Framework::Graphics::PerspectiveCamera> mPerspectiveCamera;
    std::unique_ptr<Framework::ImGUI::Window> mUIWindow;
};