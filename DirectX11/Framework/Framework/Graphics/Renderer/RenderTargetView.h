#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Resource/Texture2D.h"
#include "Framework/Utility/Property.h"
#include "Framework/Graphics/Renderer/Viewport.h"

namespace Framework {
    namespace Graphics {
        /**
        * @class RenderTargetView
        * @brief �����_�[�^�[�Q�b�g�r���[
        */
        class RenderTargetView {
        public:
            /**
            * @brief �R���X�g���N�^
            * @param texture ���\�[�X�e�N�X�`��
            * @param desc �����_�[�^�[�Q�b�g�r���[�̐ݒ�
            * @param backColor �w�i�F
            */
            RenderTargetView(ID3D11Device* device, std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Viewport& viewport, const Color4& backColor);
            /**
            * @brief �R���X�g���N�^
            * @param texture ���\�[�X�e�N�X�`��
            * @param desc �����_�[�^�[�Q�b�g�r���[�̐ݒ�
            * @param depthStencilTexture �[�x�E�X�e���V���r���[�e�N�X�`��
            * @param dsvDesc �[�x�E�X�e���V���r���[�̐ݒ�
            * @param backColor �w�i�F
            */
            RenderTargetView(ID3D11Device* device, std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
                std::shared_ptr<Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc, const Viewport& viewport, const Color4& backColor);
            /**
            * @brief �f�X�g���N�^
            */
            ~RenderTargetView();
            /**
            * @brief �����_�[�^�[�Q�b�g�r���[���擾����
            */
            ComPtr<ID3D11RenderTargetView> getRenderTargetView() const;
            /**
            * @brief �����_�[�^�[�Q�b�g�̃N���A
            */
            void clear(ID3D11DeviceContext* context);
            /**
            * @brief �����_�[�^�[�Q�b�g���Z�b�g����
            */
            void set(ID3D11DeviceContext* context);
            /**
            * @brief �`��I��
            */
            void end(ID3D11DeviceContext* context);
        private:
            ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< �����_�[�^�[�Q�b�g�r���[
            ComPtr<ID3D11DepthStencilView> mDepthStencilView; //!< �[�x�E�X�e���V���r���[
            Viewport mViewport; //!< �r���[�|�[�g
        private:
            PROPERTY(Color4, mBackColor, BackColor);
            PROPERTY(bool, mEnableDepthStencil, EnableDepthStencil);
        };

    } //Graphics 
} //Framework 
