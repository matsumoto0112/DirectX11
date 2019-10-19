#include "VertexShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/DXHelper.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
    namespace Graphics {

        VertexShader::VertexShader(ID3D11Device* device, const std::string& filepath) {
            //シェーダファイルの読み込み
            std::vector<BYTE> shaderData = Utility::ByteReader(addCSOIfNotExist(filepath)).get();
            const UINT shaderSize = shaderData.size();

            //シェーダファイルの解析
            BYTE* pInStruct = nullptr;
            for (unsigned long i = 0L; i < shaderSize - 4; i++) {
                if (memcmp(&shaderData[i], "ISGN", 4) == NULL) {
                    pInStruct = &shaderData.at(i);
                    break;
                }
            }
            if (pInStruct == nullptr) {
                MY_ASSERTION(false, "入力エレメントが解析できません");
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
                    case D3D10_REGISTER_COMPONENT_TYPE::D3D10_REGISTER_COMPONENT_FLOAT32:
                        format[i] = DXGI_FORMAT_R32G32B32A32_FLOAT;
                        break;
                    default:
                        format[i] = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
                        break;
                    }
                    break;
                    //三次元
                case '\x07':
                    switch (variant) {
                    case D3D10_REGISTER_COMPONENT_TYPE::D3D10_REGISTER_COMPONENT_FLOAT32:
                        format[i] = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
                        break;
                    default:
                        format[i] = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
                        break;
                    }
                    break;
                    //二次元
                case '\x03':
                    switch (variant) {
                    case D3D10_REGISTER_COMPONENT_TYPE::D3D10_REGISTER_COMPONENT_FLOAT32:
                        format[i] = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
                        break;
                    default:
                        format[i] = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
                        break;
                    }
                    break;
                    //一次元
                case '\x01':
                    switch (variant) {
                    case D3D10_REGISTER_COMPONENT_TYPE::D3D10_REGISTER_COMPONENT_FLOAT32:
                        format[i] = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
                        break;
                    case D3D10_REGISTER_COMPONENT_TYPE::D3D10_REGISTER_COMPONENT_UINT32:
                        format[i] = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
                        break;
                    default:
                        format[i] = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
                        break;
                    }
                    break;
                default:
                    format[i] = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
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
            throwIfFailed(device->CreateVertexShader(shaderData.data(), shaderSize, nullptr, &mVertexShader));
            throwIfFailed(device->CreateInputLayout(descs.data(), static_cast<UINT>(descs.size()),
                shaderData.data(), shaderSize, &mInputLayout));
        }

        VertexShader::~VertexShader() { }

        void VertexShader::set(ID3D11DeviceContext* context) {
            context->VSSetShader(mVertexShader.Get(), nullptr, 0);
            context->IASetInputLayout(mInputLayout.Get());
        }

    } //Graphics 
} //Framework 
