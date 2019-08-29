#pragma once
#include <d3d11.h>
#include <vector>
#include "Framework/Math/Rect.h"

namespace Framework {
namespace Graphics {

/**
* @class MultiViewport
* @brief �}���`�����_�[�^�[�Q�b�g�Ɏg�p����r���[�|�[�g
*/
class MultiViewport {
public:
    /**
    * @brief �R���X�g���N�^
    */
    MultiViewport(UINT viewportNum, const Math::Rect& rect);
    /**
    * @brief �f�X�g���N�^
    */
    ~MultiViewport();
    /**
    * @brief �r���[�|�[�g���R���e�L�X�g�ɃZ�b�g����
    */
    void set();
private:
    std::vector<D3D11_VIEWPORT> mViewports; //!< �r���[�|�[�g�z��
};

} //Graphics 
} //Framework 