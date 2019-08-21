#include "PixelShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

PixelShader::PixelShader(const std::string& filename)
    : ShaderBase(), mShaderData(std::make_unique<PixelShaderData>()) {
    create(filename);
}

PixelShader::~PixelShader() {}

void PixelShader::create(const std::string& name) {
    //�t�@�C���p�X�̍쐬
    const std::string filename = Define::Path::getInstance().shader() + name + ".cso";
    //�V�F�[�_�t�@�C���̓ǂݍ���
    std::vector<BYTE> byteData = mByteReader->read(filename);
    //�V�F�[�_�t�@�C���쐬
    Utility::getDevice()->CreatePixelShader(byteData.data(), byteData.size(), nullptr, &mShaderData->mPixelShader);
}

void PixelShader::set() {
    Utility::getContext()->PSSetShader(mShaderData->mPixelShader.Get(), nullptr, 0);
}

} //Graphics 
} //Framework 
