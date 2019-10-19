#pragma once

#include <vector>
#include <d3d11.h>
#include "Framework/Graphics/Buffer/PrimitiveTopology.h"

namespace Framework {
    namespace Graphics {

        /**
        * @class IndexBuffer
        * @brief インデックスバッファ管理クラス
        */
        class IndexBuffer {
        public:
            /**
            * @brief コンストラクタ
            * @param device デバイス
            * @param indices インデックスデータ
            * @param topology プリミティブトポロジーの種類
            */
            IndexBuffer(ID3D11Device* device, const std::vector<UINT>& indices, PrimitiveTopology topology);
            /**
            * @brief デストラクタ
            */
            ~IndexBuffer();
            /**
            * @brief インデックスデータのセット
            */
            void set(ID3D11DeviceContext* context);
            /**
            * @brief 描画指令を送る
            */
            void drawCall(ID3D11DeviceContext* context);
        private:
            ComPtr<ID3D11Buffer> mBuffer; //!< インデックスバッファ
            D3D11_PRIMITIVE_TOPOLOGY mTopology; //!< プリミティブトポロジーの種類
            UINT mIndexCount; //!< 頂点数
        };

    } //Graphics 
} //Framework 