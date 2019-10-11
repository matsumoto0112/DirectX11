#pragma once
#include <array>
#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @class AlphaBlend
* @brief �A���t�@�u�����h
*/
class AlphaBlend {
public:
    /**
    * @brief �R���X�g���N�^
    */
    AlphaBlend(const D3D11_BLEND_DESC& desc);
    /**
    * @brief �f�X�g���N�^
    */
    ~AlphaBlend();
    /**
    * @brief �A���t�@�u�����h���R���e�L�X�g�ɐݒ肷��
    */
    void set();
    /**
    * @brief �R���e�L�X�g�̏�Ԃ��N���A����
    */
    void clearState();
    /**
    * @brief ���݂̃u�����h�X�e�[�g���擾����
    */
    D3D11_BLEND_DESC getCurrentBlendStateDesc() const;
    /**
    * @brief �u�����h�X�e�[�g��ݒ肷��
    */
    void setBlendStateFromDesc(const D3D11_BLEND_DESC& desc);
private:
    Microsoft::WRL::ComPtr<ID3D11BlendState> mAlphaBlend; //!< �u�����h�X�e�[�g
};

} //Graphics 
} //Framework 