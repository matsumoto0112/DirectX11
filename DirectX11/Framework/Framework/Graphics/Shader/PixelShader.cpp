#include "PixelShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

PixelShader::PixelShader(const std::string& filepath)
    : ShaderBase() {
    //シェーダファイルの読み込み
    std::vector<BYTE> byteData = Utility::ByteReader(addExtendIfNotExist(filepath)).get();
    //シェーダファイル作成
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreatePixelShader(byteData.data(), byteData.size(), nullptr, &mPixelShader));
}

PixelShader::~PixelShader() { }

void PixelShader::set() {
    DX11InterfaceAccessor::getContext()->PSSetShader(mPixelShader.Get(), nullptr, 0);
}

} //Graphics 
} //Framework 
