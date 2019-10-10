#include "PixelShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

PixelShader::PixelShader(const std::string& filename)
    : ShaderBase(), mShaderData(std::make_unique<PixelShaderData>()) {
    create(filename);
}

PixelShader::~PixelShader() {}

void PixelShader::create(const std::string& name) {
    //ファイルパスの作成
    const std::string filename = Define::Path::getInstance()->shader() + name + ".cso";
    //シェーダファイルの読み込み
    std::vector<BYTE> byteData = Utility::ByteReader(filename).get();
    //シェーダファイル作成
    DX11InterfaceAccessor::getDevice()->CreatePixelShader(byteData.data(), byteData.size(), nullptr, &mShaderData->mPixelShader);
}

void PixelShader::set() {
    DX11InterfaceAccessor::getContext()->PSSetShader(mShaderData->mPixelShader.Get(), nullptr, 0);
}

} //Graphics 
} //Framework 
