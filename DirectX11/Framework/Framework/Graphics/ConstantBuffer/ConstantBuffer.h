#pragma once
#include "Framework/Graphics/ConstantBuffer/ConstantBufferStruct.h"
#include "Framework/Graphics/Resource/ShaderInputType.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
    namespace Graphics {
        /**
        * @class ConstantBuffer
        * @brief コンスタントバッファ
        */
        class ConstantBuffer {
        public:
            /**
            * @brief コンストラクタ
            * @param graphicsDevice グラフィックデバイス
            * @param inputType どのシェーダに値を設定するか
            * @param slotNum シェーダのどのスロットに値を設定するか
            */
            ConstantBuffer(ID3D11Device* device, UINT size, ShaderInputType inputType, UINT slotNumber);
            /**
            * @brief デストラクタ
            */
            virtual ~ConstantBuffer();

            void updateBuffer(ID3D11DeviceContext* context, void* data);
            /**
            * @brief バッファの値を転送する
            */
            void set(ID3D11DeviceContext* context);
            /**
            * @brief バッファの値をクリアする
            */
            void clear(ID3D11DeviceContext* context);
        private:
            ComPtr<ID3D11Buffer> mConstantBuffer; //!< コンスタントバッファ
            const ShaderInputType mInputType; //!< どのシェーダーにデータを転送するか
            const UINT mRegisterNum; //!< シェーダーの登録番号
            const UINT mSize;
        };


    } //Graphics 
} //Framework