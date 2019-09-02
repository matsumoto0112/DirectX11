#pragma once
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Transform.h"

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
    * @brief 弾を追加する
    */
    virtual void shotBullet(const Framework::Utility::Transform& transform) = 0;
};