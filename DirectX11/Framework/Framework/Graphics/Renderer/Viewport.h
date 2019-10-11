#pragma once
#include <d3d11.h>
#include "Framework/Math/Rect.h"

namespace Framework {
namespace Graphics {

/**
* @class Viewport
* @brief �r���[�|�[�g
*/
class Viewport {
public:
    /**
    * @brief �R���X�g���N�^
    * @param rect �r���[�|�[�g�͈̔�
    */
    Viewport(const Math::Rect& rect);
    /**
    * @brief �f�X�g���N�^
    */
    ~Viewport();
    /**
    * @brief �ݒ肷��
    */
    void set();
    /**
    * @brief �R���e�L�X�g�̏�Ԃ��N���A����
    */
    void clearState();
private:
    D3D11_VIEWPORT mViewport;
};

} //Graphics 
} //Framework 
