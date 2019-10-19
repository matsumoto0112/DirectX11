#include "PixelShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"

namespace Framework {
    namespace Graphics {
        //コンストラクタ
        PixelShader::PixelShader(ID3D11Device* device, const std::string& filepath) {
            //シェーダファイルの読み込み
            std::vector<BYTE> byteData = Utility::ByteReader(addCSOIfNotExist(filepath)).get();
            //シェーダファイル作成
            throwIfFailed(device->CreatePixelShader(byteData.data(), byteData.size(), nullptr, &mPixelShader));
        }

        //デストラクタ
        PixelShader::~PixelShader() { }

        //セットする
        void PixelShader::set(ID3D11DeviceContext* context) {
            context->PSSetShader(mPixelShader.Get(), nullptr, 0);
        }

    } //Graphics 
} //Framework 
