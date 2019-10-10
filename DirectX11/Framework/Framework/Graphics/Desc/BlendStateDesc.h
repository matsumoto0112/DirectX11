#pragma once
namespace Framework {
namespace Graphics {

/**
* @enum AlphaBlendType
* @brief �A���t�@�u�����h�̎��
*/
enum class AlphaBlendType {
    Default,
    Alignment,
    Add,
    Subsract,
    Multiply,
};

/**
* @class BlendStateDesc
* @brief �A���t�@�u�����h�̐ݒ�
*/
class BlendStateDesc {
public:
    /**
    * @brief �u�����h�f�X�N���擾����
    * @param blendType �A���t�@�u�����h�̎��
    */
    static const D3D11_BLEND_DESC BLEND_DESC(AlphaBlendType blendType) {
        D3D11_BLEND_DESC desc{};
        desc.AlphaToCoverageEnable = FALSE;
        desc.IndependentBlendEnable = FALSE;
        D3D11_RENDER_TARGET_BLEND_DESC blendDesc;
        switch (blendType) {
            case Framework::Graphics::AlphaBlendType::Default:
                blendDesc = DEFAULT_BLEND();
                break;
            case Framework::Graphics::AlphaBlendType::Alignment:
                blendDesc = ALIGNMENT_DESC();
                break;
            case Framework::Graphics::AlphaBlendType::Add:
                blendDesc = ADD_BLEND_DESC();
                break;
            case Framework::Graphics::AlphaBlendType::Subsract:
                blendDesc = SUBSTRACT_BLEND_DESC();
                break;
            case Framework::Graphics::AlphaBlendType::Multiply:
                blendDesc = MULTIPLE_BLEND_DESC();
                break;
        }
        for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
            desc.RenderTarget[i] = blendDesc;
        }
        return desc;
    }

    /**
    * @brief �f�t�H���g�̃u�����h�X�e�[�g���擾����
    */
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC DEFAULT_BLEND() {
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
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC ALIGNMENT_DESC() {
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
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC ADD_BLEND_DESC() {
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
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC SUBSTRACT_BLEND_DESC() {
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
    static constexpr D3D11_RENDER_TARGET_BLEND_DESC MULTIPLE_BLEND_DESC() {
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