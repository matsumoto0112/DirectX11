#pragma once

#include <vector>
#include <d3d11.h>
//#include "Framework/Graphics/Shader/ShaderBase.h"

namespace Framework {
    namespace Graphics {

        /**
        * @class VertexShader
        * @brief 頂点シェーダ
        */
        class VertexShader  {
        public:
            /**
            * @brief コンストラクタ
            * @param filepath シェーダファイル名
            */
            VertexShader(ID3D11Device* device, const std::string& filepath);
            /**
            * @brief デストラクタ
            */
            ~VertexShader();
            /**
            * @brief 頂点シェーダのセット
            */
            void set(ID3D11DeviceContext* context) ;
        private:
            ComPtr<ID3D11VertexShader> mVertexShader; //!< 頂点シェーダ
            ComPtr<ID3D11InputLayout> mInputLayout; //!< インプットレイアウト
        };
    } //Graphics 
} //Framework 
