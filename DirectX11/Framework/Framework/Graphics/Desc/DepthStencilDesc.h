#pragma once
#include <d3d11.h>
#include "Framework/Define/Window.h"
#include "Framework/Define/Render/MultiSampleQuarity.h"

namespace Framework {
namespace Graphics {

/**
* @class DepthStencil
* @brief �[�x�E�X�e���V���r���[�f�X�N
*/
class DepthStencilDesc {
public:
    static constexpr DXGI_FORMAT DefaultFormat = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT; //!< �f�t�H���g�̃t�H�[�}�b�g
    /**
    * @brief �f�t�H���g�̐[�x�E�X�e���V���r���[�f�X�N���擾����
    */
    static constexpr D3D11_DEPTH_STENCIL_VIEW_DESC getDefaultDepthStencilViewDesc() {
        D3D11_DEPTH_STENCIL_VIEW_DESC ds{};
        ds.Format = DefaultFormat;
        ds.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
        ds.Texture2D.MipSlice = 0;
        return ds;
    }
    /**
    * @brief MSAA�̐[�x�E�X�e���V���r���[�f�X�N���擾����
    */
    static constexpr D3D11_DEPTH_STENCIL_VIEW_DESC getMSAADepthStencilViewDesc() {
        D3D11_DEPTH_STENCIL_VIEW_DESC ds{};
        ds.Format = DefaultFormat;
        ds.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMS;
        ds.Texture2D.MipSlice = 0;
        return ds;
    }
    /**
    * @brief �f�t�H���g�̐[�x�E�X�e���V���r���[�p�e�N�X�`���f�X�N���擾����
    * @param width �e�N�X�`���̕�
    * @param height �e�N�X�`���̍���
    */
    static constexpr D3D11_TEXTURE2D_DESC getDefaultTexture2DDesc(UINT width, UINT height) {
        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DefaultFormat;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        return desc;
    }

    /**
* @brief MSAA�p�[�x�E�X�e���V���r���[�p�e�N�X�`���f�X�N���擾����
* @param width �e�N�X�`���̕�
* @param height �e�N�X�`���̍���
*/
    static D3D11_TEXTURE2D_DESC getMSAATexture2DDesc(UINT width, UINT height) {
        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DefaultFormat;
        desc.SampleDesc.Count = Define::MultiSampleQuarity::getInstance().RealCount;
        desc.SampleDesc.Quality = Define::MultiSampleQuarity::getInstance().RealQuarity;
        desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        return desc;
    }
};

} //Define 
} //Framework 