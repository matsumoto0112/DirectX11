#pragma once
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class CameraManager
* @brief カメラ管理
*/
class CameraManager {
public:
    /**
    * @brief コンストラクタ
    */
    CameraManager();
    /**
    * @brief デストラクタ
    */
    ~CameraManager();
private:
    PROPERTY_POINTER_ORIGINAL_GETTER_SETTER(std::shared_ptr<PerspectiveCamera>, mPerspectiveCamera, PerspectiveCamera,
        [&]() {return mPerspectiveCamera; },
        [&](std::shared_ptr<PerspectiveCamera> camera) {mPerspectiveCamera = camera; camera->render(); });
    PROPERTY_POINTER_ORIGINAL_GETTER_SETTER(std::shared_ptr<OrthographicCamera>, mOrthographicCamera, OrthographicCamera,
        [&]() {return mOrthographicCamera; },
        [&](std::shared_ptr<OrthographicCamera> camera) {mOrthographicCamera = camera; camera->render(); });
};

} //Graphics 
} //Framework 