#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"
#include "Source/Utility/DebugCamera.h"

namespace Framework {
namespace Graphics {
class AlphaBlend;
class RasterizerState;
class OrthographicCamera;
} //Graphics 
} //Framework 

/**
* @class NormalizedLambert
* @brief ディレクショナルライトテストシーン
*/
class NormalizedLambert : public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    NormalizedLambert();
    /**
    * @brief デストラクタ
    */
    ~NormalizedLambert();
    /**
    * @brief シーン読み込み処理
    */
    virtual void load(Framework::Scene::Collecter& collecter) override;
    /**
    * @brief 更新
    */
    virtual void update() override;
    /**
    * @brief シーン終了条件を満たしているか
    */
    virtual bool isEndScene() const override;
    /**
    * @brief 描画
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
    /**
    * @brief 終了処理
    */
    virtual void unload() override;
    /**
    * @brief 次のシーン
    */
    virtual Framework::Define::SceneType next() override;
private:
    std::shared_ptr<DebugCamera> m3DCamera; //!< カメラ
    std::shared_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< カメラ
    std::shared_ptr<Framework::Graphics::RasterizerState> mPrevRasterizer; //!< 前シーンのラスタライザの状態
    std::shared_ptr<Framework::Graphics::AlphaBlend> mPrevAlphaBlend; //!< 前シーンのアルファブレンドの状態
    std::unique_ptr<Framework::ImGUI::Window> mDebugWindow;
};