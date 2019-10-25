#pragma once
#include <memory>
#include <unordered_map>
#include "Framework/Utility/Property.h"
#include "Framework/Graphics/Buffer/IndexBuffer.h"
#include "Framework/Graphics/Buffer/VertexBuffer.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/Renderer/RenderTargetView.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Utility/STLExtend/ExtendUnorderedMap.h"

namespace Framework {
    namespace Graphics {
        /**
        * @class Pipeline
        * @brief �`��p�C�v���C���Ǘ��N���X
        */
        class Pipeline {
            using VertexbufferPtr = std::shared_ptr<VertexBuffer>;
            using IndexBufferPtr = std::shared_ptr<IndexBuffer>;
            using VertexShaderPtr = std::shared_ptr<VertexShader>;
            using PixelShaderPtr = std::shared_ptr<PixelShader>;
            using RenderTargetPtr = std::shared_ptr<RenderTargetView>;
            using ConstantBufferPtr = std::shared_ptr<ConstantBuffer>;
        public:
            /**
            * @brief �R���X�g���N�^
            */
            Pipeline();
            /**
            * @brief �f�X�g���N�^
            */
            virtual ~Pipeline();
            /**
            * @brief �`��p�C�v���C�����Z�b�g����
            */
            virtual void setPipeline();
            /**
            * @brief �p�C�v���C�����N���A����
            */
            void clearState();
        private:
            //�`��n�C���^�[�t�F�[�X
            PROPERTY_POINTER(VertexbufferPtr, mVertexBuffer, VertexBuffer);
            PROPERTY_POINTER(IndexBufferPtr, mIndexBuffer, IndexBuffer);
            PROPERTY_POINTER(VertexShaderPtr, mVertexShader, VertexShader);
            PROPERTY_POINTER(PixelShaderPtr, mPixelShader, PixelShader);
            PROPERTY_POINTER(RenderTargetPtr, mRenderTarget, RenderTarget);
            std::unordered_map<std::string, ConstantBufferPtr> mConstantBuffers;
        };

    } //Graphics 
} //Framework 