#pragma once
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Transform.h"

class Player;

/**
* @class IMainSceneMediator
* @brief メインシーン仲介者
*/
class IMainSceneMediator {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IMainSceneMediator() {};
    /**
    * @brief メインカメラを取得する
    */
    virtual Framework::Graphics::PerspectiveCamera* getMainCamera() = 0;
    /**
    * @brief プレイヤーポインタを取得する
    */
    virtual Player* getPlayer() = 0;
    /**
    * @brief 弾を追加する
    */
    virtual void shotBullet(const Framework::Utility::Transform& transform) = 0;
    /**
    * @brief デバッグ用ImGUIウィンドウを追加する
    */
    virtual void addDebugUI(std::shared_ptr<Framework::ImGUI::Window> window) = 0;
};