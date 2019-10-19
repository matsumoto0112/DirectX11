#pragma once

#include <string>
//#include "Framework/Graphics/Shader/ShaderBase.h"

namespace Framework {
    namespace Graphics {
        /**
        * @class PixelShader
        * @brief ピクセルシェーダ
        */
        class PixelShader {
        public:
            /**
            * @brief コンストラクタ
            * @param filepath シェーダファイル名
            */
            PixelShader(ID3D11Device* device, const std::string& filepath);
            /**
            * @brief デストラクタ
            */
            ~PixelShader();
            /**
            * @brief ピクセルシェーダのセット
            */
            void set(ID3D11DeviceContext* context);
        private:
            ComPtr<ID3D11PixelShader> mPixelShader; //!< ピクセルシェーダ
        };

    } //Graphics 
} //Framework 
