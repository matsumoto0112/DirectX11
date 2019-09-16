#include "ComputeShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

ComputeShader::ComputeShader(const std::string& filename)
    :ShaderBase(), mShaderData(std::make_unique<ComputeShaderData>()) {
    create(filename);
}

ComputeShader::~ComputeShader() {}

void ComputeShader::set() {}

void ComputeShader::create(const std::string& name) {
    //�t�@�C���p�X�̍쐬
    const std::string filename = Define::Path::getInstance().shader() + name + ".cso";
    //�V�F�[�_�t�@�C���̓ǂݍ���
    std::vector<BYTE> byteData = Utility::ByteReader(filename).get();
    //�V�F�[�_�t�@�C���쐬
    Utility::getDevice()->CreateComputeShader(byteData.data(), byteData.size(), nullptr, &mShaderData->mComputeShader);
}

} //Graphics 
} //Framework 
