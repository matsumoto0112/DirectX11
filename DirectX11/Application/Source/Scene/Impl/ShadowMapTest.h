#pragma once
#include <vector>
#include <memory>
#include "Framework/Scene/SceneBase.h"
#include "Framework/Utility/Transform.h"
#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {
class DirectionalLight;
class PointLight;
class Model;
class OrthographicCamera;
class PerspectiveCamera;
class TextureString;
class TextureBuffer;
class ShaderResourceView;
class RenderTargetView;
} //Graphics
namespace ImGUI {
class Window;
} //ImGUI 
} //Framework 


/**
* @class ShadowMapTest
* @brief 通常ライトテストシーン
*/
class ShadowMapTest : public Framework::Scene::SceneBase {
    struct GameObject {
        Framework::Utility::Transform mTransform;
        std::shared_ptr<Framework::Graphics::Model> mModel;
        void draw();
    };
public:
    /**
    * @brief コンストラクタ
    */
    ShadowMapTest();
    /**
    * @brief デストラクタ
    */
    ~ShadowMapTest();
    virtual void load(Framework::Scene::Collecter& collecter) override;

    virtual void update(float delta) override;

    virtual bool isEndScene() const override;

    virtual void draw() override;

    virtual void end() override;

    virtual Define::SceneType next() override;
private:
    std::vector<Framework::Utility::Transform> mWallTransforms;
    std::shared_ptr<Framework::Graphics::Model> mWall;
    GameObject mObject;
    std::vector<Framework::Utility::Transform> mObjectTransforms;
    GameObject mFloor;
    std::unique_ptr<Framework::Graphics::TextureString> mStr;
    std::unique_ptr<Framework::Graphics::PerspectiveCamera> mPerspectiveCamera;
    std::unique_ptr<Framework::Graphics::OrthographicCamera> mOrthographicCamera;
    std::shared_ptr<Framework::Graphics::DirectionalLight> mDirectionalLight;
    std::shared_ptr<Framework::Graphics::PointLight> mPointLight;

    std::unique_ptr<Framework::ImGUI::Window> mUIWindow;

    std::shared_ptr<Framework::Graphics::RenderTargetView> mRenderTargetView;

    std::shared_ptr<Framework::Graphics::TextureBuffer> mRenderTargetTextureBuffer;
    std::shared_ptr<Framework::Graphics::ShaderResourceView> mShaderResourceView;
};