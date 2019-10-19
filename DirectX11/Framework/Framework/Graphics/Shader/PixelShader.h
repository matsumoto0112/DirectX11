#pragma once

#include <string>
//#include "Framework/Graphics/Shader/ShaderBase.h"

namespace Framework {
    namespace Graphics {
        /**
        * @class PixelShader
        * @brief �s�N�Z���V�F�[�_
        */
        class PixelShader {
        public:
            /**
            * @brief �R���X�g���N�^
            * @param filepath �V�F�[�_�t�@�C����
            */
            PixelShader(ID3D11Device* device, const std::string& filepath);
            /**
            * @brief �f�X�g���N�^
            */
            ~PixelShader();
            /**
            * @brief �s�N�Z���V�F�[�_�̃Z�b�g
            */
            void set(ID3D11DeviceContext* context);
        private:
            ComPtr<ID3D11PixelShader> mPixelShader; //!< �s�N�Z���V�F�[�_
        };

    } //Graphics 
} //Framework 
