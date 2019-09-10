//#pragma once
//#include <vector>
//#include <memory>
//#include "Framework/Scene/SceneBase.h"
//
//namespace Framework {
//namespace Graphics {
//class Model;
//class OrthographicCamera;
//class PerspectiveCamera;
//class TextureString;
//} //Graphics
//namespace Utility {
//class Transform;
//} //Utility 
//} //Framework 
//
///**
//* @class DepthStencilTest
//* @brief discription
//*/
//class DepthStencilTest :public Framework::Scene::SceneBase {
//public:
//    /**
//    * @brief コンストラクタ
//    */
//    DepthStencilTest();
//    /**
//    * @brief デストラクタ
//    */
//    ~DepthStencilTest();
//
//    virtual void load(Framework::Scene::Collecter& collecter) override;
//
//    virtual void update() override;
//
//    virtual bool isEndScene() const override;
//
//    virtual void draw() override;
//
//    virtual void end() override;
//
//    virtual Define::SceneType next() override;
//private:
//    std::unique_ptr<Framework::Graphics::TextureString> mStr;
//    std::shared_ptr<Framework::Graphics::Model> mModel;
//    std::vector<std::unique_ptr<Framework::Utility::Transform>> mModelTransforms;
//    std::unique_ptr<Framework::Graphics::PerspectiveCamera> mPerspectiveCamera;
//    std::unique_ptr<Framework::Graphics::OrthographicCamera> mOrthographicCamera;
//};