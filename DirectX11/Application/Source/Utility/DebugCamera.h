#pragma once
#include "Framework/Graphics/Camera/PerspectiveCamera.h"

/**
* @class DebugCamera
* @brief �f�o�b�OUI�t���J����
*/
class DebugCamera :public Framework::Graphics::PerspectiveCamera {
public:
    /**
    * @brief �R���X�g���N�^
    */
    DebugCamera(const Framework::Math::ViewInfo& view, const Framework::Math::ProjectionInfo& proj);
    /**
    * @brief �f�X�g���N�^
    */
    ~DebugCamera();

    void drawControlWindow();
private:
    std::unique_ptr<Framework::ImGUI::Window> mCameraControl;
    float mLength;
};
