#pragma once
#include <d3d11.h>

namespace Framework {
namespace Graphics {

/**
* @class AlphaBlendSetting
* @brief �A���t�@�u�����h�̐ݒ�
*/
class AlphaBlendSetting {
public:
    /**
    * @brief �f�t�H���g�̃u�����h�X�e�[�g���擾����
    */
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC getDefaultDesc() {
        D3D11_RENDER_TARGET_BLEND_DESC renderTarget{};
        renderTarget.BlendEnable = FALSE;
        renderTarget.SrcBlend = D3D11_BLEND_ONE;
        renderTarget.DestBlend = D3D11_BLEND_ZERO;
        renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
        renderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
        renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
        renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        return renderTarget;
    }

    /**
    * @brief ���`�����p�u�����h�X�e�[�g���擾����
    */
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC getAlignmentBlendDesc() {
        D3D11_RENDER_TARGET_BLEND_DESC renderTarget{};
        renderTarget.BlendEnable = TRUE;
        renderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
        renderTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
        renderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
        renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
        renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        return renderTarget;
    }

    /**
    * @brief ���Z�����p�u�����h�X�e�[�g���擾����
    */
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC getAddBlendDesc() {
        D3D11_RENDER_TARGET_BLEND_DESC renderTarget{};
        renderTarget.BlendEnable = TRUE;
        renderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
        renderTarget.DestBlend = D3D11_BLEND_ONE;
        renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
        renderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
        renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
        renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        return renderTarget;
    }

    /**
    * @brief ���Z�����p�u�����h�X�e�[�g���擾����
    */
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC getSubtractBlendDesc() {
        D3D11_RENDER_TARGET_BLEND_DESC renderTarget{};
        renderTarget.BlendEnable = TRUE;
        renderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
        renderTarget.DestBlend = D3D11_BLEND_ONE;
        renderTarget.BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
        renderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
        renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
        renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        return renderTarget;
    }

    /**
    * @brief ��Z�����p�u�����h�X�e�[�g���擾����
    */
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC getMultipleBlendDesc() {
        D3D11_RENDER_TARGET_BLEND_DESC renderTarget{};
        renderTarget.BlendEnable = TRUE;
        renderTarget.SrcBlend = D3D11_BLEND_ZERO;
        renderTarget.DestBlend = D3D11_BLEND_SRC_COLOR;
        renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
        renderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
        renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
        renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        return renderTarget;
    }
};
} //Graphics 
} //Framework 