#pragma once
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Camera
* @brief カメラ基底クラス
*/
class Camera {
public:
    /**
    * @brief コンストラクタ
    */
    Camera(const Math::Matrix4x4& view, const Math::Matrix4x4& proj);
    /**
    * @brief デストラクタ
    */
    ~Camera();

    virtual void setMatrix();
private:
    PROPERTY(Math::Matrix4x4, mView, View);
    PROPERTY(Math::Matrix4x4, mProjection, Projection);
};

} //Graphics 
} //Framework 