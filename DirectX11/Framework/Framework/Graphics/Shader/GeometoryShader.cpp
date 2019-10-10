#include "GeometoryShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

GeometoryShader::GeometoryShader(const std::string& filepath)
    : ShaderBase() {
    //シェーダファイルの読み込み
    std::vector<BYTE> byteData = Utility::ByteReader(filepath).get();
    //シェーダファイル作成
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateGeometryShader(byteData.data(), byteData.size(), nullptr, &mGeometoryShader));
}

GeometoryShader::~GeometoryShader() { }

void GeometoryShader::set() {
    DX11InterfaceAccessor::getContext()->GSSetShader(mGeometoryShader.Get(), nullptr, 0);
}

} //Graphics 
} //Framework 
