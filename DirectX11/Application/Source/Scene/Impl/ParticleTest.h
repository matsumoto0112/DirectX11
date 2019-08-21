#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class TextureString;
class SimpleParticleEmitter;
} //Graphics 
} //Framework 

/**
* @class ParticleTest
* @brief パーティクルテストシーン
*/
class ParticleTest :public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    ParticleTest();
    /**
    * @brief デストラクタ
    */
    ~ParticleTest();
    /**
    * @brief シーンデータの読み込み
    */
    virtual void load(Framework::Scene::Collecter& collecter) override;
    /**
    * @brief 更新
    */
    virtual void update(float delta) override;
    /**
    * @brief 終了しているか
    */
    virtual bool isEndScene() const override;
    /**
    * @brief 描画
    */
    virtual void draw() override;
    /**
    * @brief 終了処理
    */
    virtual void end() override;
    /**
    * @brief 次のシーン
    */
    virtual Define::SceneType next() override;
private:
    std::unique_ptr<Framework::Graphics::TextureString> mParticleStr;
    std::unique_ptr<Framework::Graphics::SimpleParticleEmitter> mParticle;
};
