#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"
#include "Source/GameObject/IMainSceneMediator.h"

namespace Framework {
namespace Graphics {
class AlphaBlend;
class Model;
class PerspectiveCamera;
} //Graphics 
} //Framework 

class GameObjectManager;
class FollowCamera;

/**
* @class Main
* @brief メインシーン実装クラス
*/
class Main : public Framework::Scene::SceneBase, public IMainSceneMediator {
public:
    /**
    * @brief コンストラクタ
    */
    Main();
    /**
    * @brief デストラクタ
    */
    ~Main();
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
    virtual Define::SceneType next() override;
    /**
    * @brief メインカメラを取得する
    */
    virtual FollowCamera* getMainCamera() override;
    /**
    * @brief プレイヤーポインタを取得する
    */
    virtual Player * getPlayer() override;
    /**
    * @brief 弾を発射する
    */
    virtual void shotBullet(const Framework::Utility::Transform& transform) override;
    /**
    * @brief デバッグUIを追加する
    */
    virtual void addDebugUI(std::shared_ptr<Framework::ImGUI::Window> window) override;
private:
    std::unique_ptr<GameObjectManager> mManager;
    std::unique_ptr<FollowCamera> mCamera;
    std::unique_ptr<Framework::Graphics::AlphaBlend> mAlphaBlend;
private:
    std::vector<std::shared_ptr<Framework::ImGUI::Window>> mDebugUIs;
};