#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class Model;
} //Graphics 
} //Framework 

class GameObjectManager;

/**
* @class Main
* @brief メインシーン実装クラス
*/
class Main : public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    Main();
    /**
    * @brief デストラクタ
    */
    ~Main();
    virtual void load(Framework::Scene::Collecter& collecter) override;

    virtual void update(float delta) override;

    virtual bool isEndScene() const override;

    virtual void draw() override;

    virtual void end() override;

    virtual Define::SceneType next() override;
private:
    std::unique_ptr<GameObjectManager> mManager;
};