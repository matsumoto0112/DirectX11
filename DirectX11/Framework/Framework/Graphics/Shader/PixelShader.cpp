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
    //�t�@�C���p�X�̍쐬
    const std::string filename = Define::Path::getInstance()->shader() + name + ".cso";
    //�V�F�[�_�t�@�C���̓ǂݍ���
    std::vector<BYTE> byteData = Utility::ByteReader(filename).get();
    //�V�F�[�_�t�@�C���쐬
    DX11InterfaceAccessor::getDevice()->CreatePixelShader(byteData.data(), byteData.size(), nullptr, &mShaderData->mPixelShader);
}

void PixelShader::set() {
    DX11InterfaceAccessor::getContext()->PSSetShader(mShaderData->mPixelShader.Get(), nullptr, 0);
}

} //Graphics 
} //Framework 
