#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class PerspectiveCamera;
} //Graphics 
} //Framework 

/**
* @class RenderModel
* @brief モデル描画テストシーン
*/
class RenderModel : public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    RenderModel();
    /**
    * @brief デストラクタ
    */
    ~RenderModel();
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
    std::shared_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< カメラ
};