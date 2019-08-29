#pragma once
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @class MultiRenderTarget
* @brief �}���`�����_�[�^�[�Q�b�g
*/
class MultiRenderTarget {
public:
    /**
    * @brief �R���X�g���N�^
    */
    MultiRenderTarget(UINT renderTargetNum);
    /**
    * @brief �f�X�g���N�^
    */
    ~MultiRenderTarget();
private:
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView[]> mRTVs;
};

} //Graphics 
} //Framework 