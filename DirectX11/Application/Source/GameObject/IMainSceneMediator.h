#pragma once

#include "Framework/Graphics/Camera/PerspectiveCamera.h"

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
};