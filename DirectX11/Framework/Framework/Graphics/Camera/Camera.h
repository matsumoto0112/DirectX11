#pragma once
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Camera
* @brief �J�������N���X
*/
class Camera {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Camera(const Math::Matrix4x4& view, const Math::Matrix4x4& proj);
    /**
    * @brief �f�X�g���N�^
    */
    ~Camera();

    virtual void setMatrix();
private:
    PROPERTY(Math::Matrix4x4, mView, View);
    PROPERTY(Math::Matrix4x4, mProjection, Projection);
};

} //Graphics 
} //Framework 