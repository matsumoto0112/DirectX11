#include "GeometoryShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

GeometoryShader::GeometoryShader(const std::string& filename)
    : ShaderBase(), mShaderData(std::make_unique<GeometoryShaderData>()) {
    create(filename);
}

GeometoryShader::~GeometoryShader() {}

void GeometoryShader::set() {   
    DX11InterfaceAccessor::getContext()->GSSetShader(mShaderData->mGeometoryShader.Get(), nullptr, 0);
}

void GeometoryShader::create(const std::string& name) { 
    //ファイルパスの作成
    const std::string filename = Define::Path::getInstance()->shader() + name + ".cso";
    //シェーダファイルの読み込み
    std::vector<BYTE> byteData = Utility::ByteReader(filename).get();
    //シェーダファイル作成
    DX11InterfaceAccessor::getDevice()->CreateGeometryShader(byteData.data(), byteData.size(), nullptr, &mShaderData->mGeometoryShader);
}

} //Graphics 
} //Framework 
