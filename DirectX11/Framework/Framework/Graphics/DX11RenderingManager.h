#pragma once
#include "Framework/Graphics/Buffer/IndexBuffer.h"
#include "Framework/Graphics/Buffer/VertexBuffer.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/Renderer/RenderTargetView.h"

namespace Framework {
    namespace Graphics {
        /**
        * @class DX11RenderingManager
        * @brief DirectX11�p�`��Ǘ���
        */
        class DX11RenderingManager : public Utility::Singleton<DX11RenderingManager> {
            using VertexbufferPtr = std::shared_ptr<VertexBuffer>;
            using IndexBufferPtr = std::shared_ptr<IndexBuffer>;
            using VertexShaderPtr = std::shared_ptr<VertexShader>;
            using PixelShaderPtr = std::shared_ptr<PixelShader>;
            using RenderTargetPtr = std::shared_ptr<RenderTargetView>;
        public:
            /**
            * @brief ����������
            */
            bool init(HWND hWnd, UINT width, UINT height, UINT frameCount = 2, bool isFullScreen = false);
            void setVertexBuffer(VertexbufferPtr vertexBuffer);
            void setIndexBuffer(IndexBufferPtr indexBuffer);
            void setVertexShader(VertexShaderPtr vertexShader);
            void setPixelShader(PixelShaderPtr pixelShader);
            void setRenderTarget(RenderTargetPtr renderTarget);
            void draw();
            void beginFrame();
            void endFrame();

            template<class T>
            VertexbufferPtr createVertexBuffer(const std::vector<T>& vertices);
            IndexBufferPtr createIndexBuffer(const std::vector<UINT>& indices, PrimitiveTopology primitiveTopology);
            VertexShaderPtr createVertexShader(const std::string& filename);
            PixelShaderPtr createPixelShader(const std::string& filename);
            //RenderTargetPtr createRenderTarget();
        protected:
            /**
            * @brief �R���X�g���N�^
            */
            DX11RenderingManager();
            /**
            * @brief �f�X�g���N�^
            */
            ~DX11RenderingManager();
        private:
            //DirectX�n�C���^�[�t�F�[�X
            ComPtr<ID3D11Device> mDevice; //!< �f�o�C�X
            ComPtr<ID3D11DeviceContext> mImmediateContext; //!< �f�o�C�X�R���e�L�X�g 
            ComPtr<IDXGISwapChain> mSwapChain; //!< �X���b�v�`�F�C��
            ComPtr<ID3D11Debug> mDebug; //!< �f�o�b�O
            UINT mFrameCount;

            //�`��n�C���^�[�t�F�[�X
            VertexbufferPtr mVertexBuffer;
            IndexBufferPtr mIndexBuffer;
            VertexShaderPtr mVertexShader;
            PixelShaderPtr mPixelShader;
            RenderTargetPtr mRenderTarget;
            RenderTargetPtr mBackBuffer;
        };

        template<class T>
        inline std::shared_ptr<VertexBuffer> DX11RenderingManager::createVertexBuffer(const std::vector<T>& vertices) {
            return std::make_shared<VertexBuffer>(mDevice.Get(), vertices);
        }

    } //Graphics 
} //Framework 