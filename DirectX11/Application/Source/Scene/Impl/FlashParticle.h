#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class AlphaBlend;
class OrthographicCamera;
class PerspectiveCamera;
} //Graphics 
} //Framework 

/**
* @class FlashParticle
* @brief 閃光パーティクルテストシーン
*/
class FlashParticle : public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    FlashParticle();
    /**
    * @brief デストラクタ
    */
    ~FlashParticle();
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
    virtual void end() override;
    /**
    * @brief 次のシーン
    */
    virtual Framework::Define::SceneType next() override;
private:
    std::unique_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< カメラ
    std::unique_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< カメラ
    std::unique_ptr<Framework::Graphics::AlphaBlend> mAlphaBlend;
};