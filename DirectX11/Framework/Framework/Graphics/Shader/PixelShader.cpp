#include "PixelShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/IO/ByteReader.h"

namespace Framework {
    namespace Graphics {
        //�R���X�g���N�^
        PixelShader::PixelShader(ID3D11Device* device, const std::string& filepath) {
            //�V�F�[�_�t�@�C���̓ǂݍ���
            std::vector<BYTE> byteData = Utility::ByteReader(addCSOIfNotExist(filepath)).get();
            //�V�F�[�_�t�@�C���쐬
            throwIfFailed(device->CreatePixelShader(byteData.data(), byteData.size(), nullptr, &mPixelShader));
        }

        //�f�X�g���N�^
        PixelShader::~PixelShader() { }

        //�Z�b�g����
        void PixelShader::set(ID3D11DeviceContext* context) {
            context->PSSetShader(mPixelShader.Get(), nullptr, 0);
        }

    } //Graphics 
} //Framework 
