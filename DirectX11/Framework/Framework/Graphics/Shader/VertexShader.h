#pragma once

#include <vector>
#include <d3d11.h>
//#include "Framework/Graphics/Shader/ShaderBase.h"

namespace Framework {
    namespace Graphics {

        /**
        * @class VertexShader
        * @brief ���_�V�F�[�_
        */
        class VertexShader  {
        public:
            /**
            * @brief �R���X�g���N�^
            * @param filepath �V�F�[�_�t�@�C����
            */
            VertexShader(ID3D11Device* device, const std::string& filepath);
            /**
            * @brief �f�X�g���N�^
            */
            ~VertexShader();
            /**
            * @brief ���_�V�F�[�_�̃Z�b�g
            */
            void set(ID3D11DeviceContext* context) ;
        private:
            ComPtr<ID3D11VertexShader> mVertexShader; //!< ���_�V�F�[�_
            ComPtr<ID3D11InputLayout> mInputLayout; //!< �C���v�b�g���C�A�E�g
        };
    } //Graphics 
} //Framework 
