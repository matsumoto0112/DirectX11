#include "GeometoryShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

GeometoryShader::GeometoryShader(const std::string& filename)
    : ShaderBase(), mShaderData(std::make_unique<GeometoryShaderData>()) {
    create(filename);
}

GeometoryShader::~GeometoryShader() {}

void GeometoryShader::set() {   
    Utility::getContext()->GSSetShader(mShaderData->mGeometoryShader.Get(), nullptr, 0);
}

void GeometoryShader::create(const std::string& name) { 
    //�t�@�C���p�X�̍쐬
    const std::string filename = Define::Path::getInstance().shader() + name + ".cso";
    //�V�F�[�_�t�@�C���̓ǂݍ���
    std::vector<BYTE> byteData = Utility::ByteReader(filename).get();
    //�V�F�[�_�t�@�C���쐬
    Utility::getDevice()->CreateGeometryShader(byteData.data(), byteData.size(), nullptr, &mShaderData->mGeometoryShader);
}

} //Graphics 
} //Framework 
