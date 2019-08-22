#pragma once
#include <vector>
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class Model;
class PerspectiveCamera;
} //Graphics
namespace Utility {
class Transform;
} //Utility 
} //Framework 

/**
* @class DepthStencilTest
* @brief discription
*/
class DepthStencilTest :public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    DepthStencilTest();
    /**
    * @brief デストラクタ
    */
    ~DepthStencilTest();

    virtual void load(Framework::Scene::Collecter& collecter) override;

    virtual void update(float delta) override;

    virtual bool isEndScene() const override;

    virtual void draw() override;

    virtual void end() override;

    virtual Define::SceneType next() override;
private:
    std::shared_ptr<Framework::Graphics::Model> mModel;
    std::vector<std::unique_ptr<Framework::Utility::Transform>> mModelTransforms;
    std::unique_ptr<Framework::Graphics::PerspectiveCamera> mPerspectiveCamera;
};