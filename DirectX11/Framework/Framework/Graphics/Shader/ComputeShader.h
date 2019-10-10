#pragma once

#include <string>
#include <vector>
#include "Framework/Graphics/Shader/ShaderBase.h"
#include "Framework/Graphics/Shader/ComputeShaderData.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
/**
* @class PixelShader
* @brief �s�N�Z���V�F�[�_
*/
class ComputeShader : public ShaderBase {
public:
    /**
    * @struct Info
    * @brief �R���s���[�g�V�F�[�_���
    */
    struct Info {
        UINT dispatchX;
        UINT dispatchY;
        UINT dispatchZ;
        UINT threadX;
        UINT threadY;
        UINT threadZ;
    };
    /**
    * @struct SRV
    * @brief �V�F�[�_���\�[�X�r���[���
    */
    struct SRV {
        UINT registerNum; //!< ���W�X�^�[�ԍ�
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer; //!< �o�b�t�@
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv; //!< �V�F�[�_�[���\�[�X�r���[
    };
    /**
    * @struct UAV
    * @brief �A���I�[�_�[�h�A�N�Z�X�r���[���
    */
    struct UAV {
        UINT registerNum; //!< ���W�X�^�[�ԍ�
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer; //!< �o�b�t�@
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> uav; //!< �A���I�[�_�[�h�A�N�Z�X�r���[
    };
    /**
    * @struct Buffer
    * @brief �o�b�t�@���
    */
    struct VertexBuffer {
        UINT registerNum; //!< ���W�X�^�[�ԍ�
        UINT stride;
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer; //!< �o�b�t�@
    };
public:
    /**
    * @brief �R���X�g���N�^
    * @param filename �V�F�[�_�t�@�C����
    */
    ComputeShader(const std::string& filename, const Info& info);
    /**
    * @brief �f�X�g���N�^
    */
    ~ComputeShader();
    /**
    * @brief �R���s���[�g�V�F�[�_�̃Z�b�g
    */
    void set();
    /**
    * @brief �V�F�[�_�[���\�[�X�r���[���쐬����
    * @tparam T �f�[�^�Ƃ��Ďg�p����\����
    * @param registerNum ���W�X�^�[�ԍ�
    * @param data ���\�[�X�Ɏg�p����f�[�^�z��
    */
    template <class T>
    void addSRV(UINT registerNum, const std::vector<T>& data);

    /**
    * @brief �A���I�[�_�[�h�A�N�Z�X�r���[���쐬����
    * @tparam T �f�[�^�Ƃ��Ďg�p����\����
    * @param registerNum ���W�X�^�[�ԍ�
    * @param data �������݌��ƂȂ�f�[�^�z��
    */
    template <class T>
    void addUAV(UINT registerNum, const std::vector<T>& data);
    /**
    * @brief ���_�o�b�t�@�Ƃ��Ă��g�p�ł���A���I�[�_�[�h�A�N�Z�X�r���[���쐬����
    * @tparam T �f�[�^�Ƃ��Ďg�p����\����
    * @param registerNum ���W�X�^�[�ԍ�
    * @param data �������݌��ƂȂ�f�[�^�z��
    * @param vertexBufferRegisterNum ���_�o�b�t�@�̃��W�X�^�[�ԍ�
    */
    template <class T>
    void addUAVEnableVertexBuffer(UINT registerNum, const std::vector<T>& data, UINT vertexBufferRegisterNum = 0);
    /**
    * @brief ���_�o�b�t�@���Z�b�g����
    */
    void setToVertexBuffer();
    /**
    * @brief ���_�o�b�t�@���N���A����
    * @details UAV���g�p����Ƃ��ɓ������\�[�X�����_�o�b�t�@�ɃZ�b�g����Ă���Ɠ��삵�Ȃ��̂ŕ`��I����ɕK���Ă�
    */
    void clearVertexBuffer();
private:
    /**
    * @brief �s�N�Z���V�F�[�_�̍쐬
    * @param name �V�F�[�_�t�@�C����
    */
    void create(const std::string& name);
private:
    PROPERTY_READONLY(Info, mInfo, Info); //!< �R���s���[�g�V�F�[�_���
private:
    std::unique_ptr<ComputeShaderData> mShaderData; //!< �V�F�[�_�[�̃f�[�^
    std::vector<SRV> mSRVs; //!< �V�F�[�_���\�[�X�r���[�z��
    std::vector<UAV> mUAVs; //!< �A���I�[�_�[�h�A�N�Z�X�r���[�z��
    std::vector<VertexBuffer> mVertexBuffers; //!< ���_�o�b�t�@�z��
};

template<class T>
inline void ComputeShader::addSRV(UINT registerNum, const std::vector<T>& dataArray) {
    SRV srv;
    srv.registerNum = registerNum;

    int elemSize = sizeof(T);
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = elemSize * static_cast<UINT>(dataArray.size());
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    desc.StructureByteStride = elemSize;

    D3D11_SUBRESOURCE_DATA sub;
    sub.pSysMem = dataArray.data();

    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &sub, &srv.buffer);
    MY_ASSERTION(SUCCEEDED(hr), "���s");

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    srvDesc.BufferEx.FirstElement = 0;
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.BufferEx.NumElements = desc.ByteWidth / 4;

    //NumElements�͍\���̗̂v�f���B�����悻�̏ꍇ4Byte�ϐ����g���Ă���Ɨ\�z�����̂�4�Ŋ���
    const int numElem = desc.ByteWidth / 4;
    srvDesc.BufferEx.NumElements = numElem;

    hr = DX11InterfaceAccessor::getDevice()->CreateShaderResourceView(srv.buffer.Get(), &srvDesc, &srv.srv);
    MY_ASSERTION(SUCCEEDED(hr), "���s");

    mSRVs.emplace_back(srv);
}

template<class T>
inline void ComputeShader::addUAV(UINT registerNum, const std::vector<T>& data) {
    UAV uav;
    uav.registerNum = registerNum;

    UINT elemSize = sizeof(T);

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;;
    desc.ByteWidth = elemSize * static_cast<UINT>(data.size());
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    desc.StructureByteStride = elemSize;

    D3D11_SUBRESOURCE_DATA sub;
    sub.pSysMem = data.data();

    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &sub, &uav.buffer);
    MY_ASSERTION(SUCCEEDED(hr), "���s");
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    //NumElements�͍\���̗̂v�f���B�����悻�̏ꍇ4Byte�ϐ����g���Ă���Ɨ\�z�����̂�4�Ŋ���
    const int numElem = desc.ByteWidth / 4;
    uavDesc.Buffer.NumElements = numElem;

    hr = DX11InterfaceAccessor::getDevice()->CreateUnorderedAccessView(uav.buffer.Get(), &uavDesc, &uav.uav);
    MY_ASSERTION(SUCCEEDED(hr), "���s");

    mUAVs.emplace_back(uav);
}

template<class T>
inline void ComputeShader::addUAVEnableVertexBuffer(UINT registerNum, const std::vector<T>& data, UINT vertexBufferRegisterNum) {
    UAV uav;
    uav.registerNum = registerNum;

    UINT elemSize = sizeof(T);

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;;
    desc.ByteWidth = elemSize * static_cast<UINT>(data.size());
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    desc.StructureByteStride = elemSize;

    D3D11_SUBRESOURCE_DATA sub;
    sub.pSysMem = data.data();

    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &sub, &uav.buffer);
    MY_ASSERTION(SUCCEEDED(hr), "���s");
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    //NumElements�͍\���̗̂v�f���B�����悻�̏ꍇ4Byte�ϐ����g���Ă���Ɨ\�z�����̂�4�Ŋ���
    const int numElem = desc.ByteWidth / 4;
    uavDesc.Buffer.NumElements = numElem;

    hr = DX11InterfaceAccessor::getDevice()->CreateUnorderedAccessView(uav.buffer.Get(), &uavDesc, &uav.uav);
    MY_ASSERTION(SUCCEEDED(hr), "���s");

    mUAVs.emplace_back(uav);

    mVertexBuffers.emplace_back(VertexBuffer{ vertexBufferRegisterNum,elemSize,uav.buffer });
}

} //Graphics 
} //Framework 
