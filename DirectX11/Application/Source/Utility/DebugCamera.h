#pragma once
#include "Framework/Graphics/Camera/PerspectiveCamera.h"

/**
* @class DebugCamera
* @brief デバッグUI付きカメラ
*/
class DebugCamera :public Framework::Graphics::PerspectiveCamera {
public:
    /**
    * @brief コンストラクタ
    */
    DebugCamera(const Framework::Math::ViewInfo& view, const Framework::Math::ProjectionInfo& proj);
    /**
    * @brief デストラクタ
    */
    ~DebugCamera();

    void drawControlWindow();
private:
    std::unique_ptr<Framework::ImGUI::Window> mCameraControl;
    float mLength;
};
