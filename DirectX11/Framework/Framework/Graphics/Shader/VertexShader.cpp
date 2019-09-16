#include "VertexShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

VertexShader::VertexShader(const std::string& name)
    :ShaderBase(), mShaderData(std::make_unique<VertexShaderData>()) {
    create(name);
}

VertexShader::VertexShader(const std::string& name, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayouts)
    : ShaderBase(), mShaderData(std::make_unique<VertexShaderData>()) {
    ID3D11Device* device = Utility::getDevice();
    //ファイルパスの作成
    const std::string filepath = Define::Path::getInstance().shader() + name + ".cso";
    //シェーダファイルの読み込み
    std::vector<BYTE> shaderData = Utility::ByteReader(filepath).get();
    const UINT shaderSize = shaderData.size();

    //シェーダファイル作成
    HRESULT hr = device->CreateVertexShader(shaderData.data(), shaderSize, nullptr, &mShaderData->mVertexShader);
    MY_ASSERTION(SUCCEEDED(hr), "VertexShader作成失敗\n" + filepath);
    hr = device->CreateInputLayout(inputLayouts.data(), inputLayouts.size(),
        shaderData.data(), shaderSize, &mShaderData->mInputLayout);
    MY_ASSERTION(SUCCEEDED(hr), "InputLayout作成失敗");

}

VertexShader::~VertexShader() {}

void VertexShader::create(const std::string& name) {
    ID3D11Device* device = Utility::getDevice();
    //ファイルパスの作成
    const std::string filepath = Define::Path::getInstance().shader() + name + ".cso";
    //シェーダファイルの読み込み
    std::vector<BYTE> shaderData = Utility::ByteReader(filepath).get();
    const UINT shaderSize = shaderData.size();

    unsigned char *pInStruct = nullptr;
    for (unsigned long i = 0L; i < shaderSize - 4; i++) {
        if (memcmp(&shaderData[i], "ISGN", 4) == NULL) {
            pInStruct = &shaderData[i];
            break;
        }
    }
    if (pInStruct == nullptr) {
        return;
    }

    //変数の数
    int cntVariable = pInStruct[8];
    std::vector<std::string>semanticsName(cntVariable);
    std::vector<UINT> semanticsIndex(cntVariable);
    std::vector<DXGI_FORMAT> format(cntVariable);
    unsigned char* str = &pInStruct[16];
    for (int i = 0; i < cntVariable; i++) {
        semanticsName[i] = std::string((char*)(str[i * 24] + pInStruct + 8));
        semanticsIndex[i] = str[i * 24 + 4];
        //ベクトルの次元数
        const char dimension = str[i * 24 + 20];
        //型の種類
        const char variant = str[i * 24 + 12];
        switch (dimension) {
            //四次元
        case '\x0f':
            switch (variant) {
            case D3D10_REGISTER_COMPONENT_FLOAT32:
                format[i] = DXGI_FORMAT_R32G32B32A32_FLOAT;
                break;
            default:
                format[i] = DXGI_FORMAT_UNKNOWN;
                break;
            }
            break;
            //三次元
        case '\x07':
            switch (variant) {
            case D3D10_REGISTER_COMPONENT_FLOAT32:
                format[i] = DXGI_FORMAT_R32G32B32_FLOAT;
                break;
            default:
                break;
            }
            break;
            //二次元
        case '\x03':
            switch (variant) {
            case D3D10_REGISTER_COMPONENT_FLOAT32:
                format[i] = DXGI_FORMAT_R32G32_FLOAT;
                break;
            default:
                format[i] = DXGI_FORMAT_UNKNOWN;
                break;
            }
            break;
            //一次元
        case '\x01':
            break;
        default:
            break;
        }
    }

    std::vector<D3D11_INPUT_ELEMENT_DESC> descs(cntVariable);
    for (int i = 0; i < cntVariable; i++) {
        descs[i] = {
            semanticsName[i].c_str(),
            semanticsIndex[i],
            format[i],
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0 };
    }

    //シェーダファイル作成
    HRESULT hr = device->CreateVertexShader(shaderData.data(), shaderSize, nullptr, &mShaderData->mVertexShader);
    MY_ASSERTION(SUCCEEDED(hr), "VertexShader作成失敗\n" + filepath);
    hr = device->CreateInputLayout(descs.data(), descs.size(),
        shaderData.data(), shaderSize, &mShaderData->mInputLayout);
    MY_ASSERTION(SUCCEEDED(hr), "InputLayout作成失敗");
}

void VertexShader::set() {
    Utility::getContext()->VSSetShader(mShaderData->mVertexShader.Get(), nullptr, 0);
    Utility::getContext()->IASetInputLayout(mShaderData->mInputLayout.Get());
}

} //Graphics 
} //Framework 
