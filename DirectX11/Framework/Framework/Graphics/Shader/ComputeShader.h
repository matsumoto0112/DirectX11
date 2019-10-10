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
* @brief ピクセルシェーダ
*/
class ComputeShader : public ShaderBase {
public:
    /**
    * @struct Info
    * @brief コンピュートシェーダ情報
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
    * @brief シェーダリソースビュー情報
    */
    struct SRV {
        UINT registerNum; //!< レジスター番号
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer; //!< バッファ
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv; //!< シェーダーリソースビュー
    };
    /**
    * @struct UAV
    * @brief アンオーダードアクセスビュー情報
    */
    struct UAV {
        UINT registerNum; //!< レジスター番号
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer; //!< バッファ
        Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> uav; //!< アンオーダードアクセスビュー
    };
    /**
    * @struct Buffer
    * @brief バッファ情報
    */
    struct VertexBuffer {
        UINT registerNum; //!< レジスター番号
        UINT stride;
        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer; //!< バッファ
    };
public:
    /**
    * @brief コンストラクタ
    * @param filename シェーダファイル名
    */
    ComputeShader(const std::string& filename, const Info& info);
    /**
    * @brief デストラクタ
    */
    ~ComputeShader();
    /**
    * @brief コンピュートシェーダのセット
    */
    void set();
    /**
    * @brief シェーダーリソースビューを作成する
    * @tparam T データとして使用する構造体
    * @param registerNum レジスター番号
    * @param data リソースに使用するデータ配列
    */
    template <class T>
    void addSRV(UINT registerNum, const std::vector<T>& data);

    /**
    * @brief アンオーダードアクセスビューを作成する
    * @tparam T データとして使用する構造体
    * @param registerNum レジスター番号
    * @param data 書き込み元となるデータ配列
    */
    template <class T>
    void addUAV(UINT registerNum, const std::vector<T>& data);
    /**
    * @brief 頂点バッファとしても使用できるアンオーダードアクセスビューを作成する
    * @tparam T データとして使用する構造体
    * @param registerNum レジスター番号
    * @param data 書き込み元となるデータ配列
    * @param vertexBufferRegisterNum 頂点バッファのレジスター番号
    */
    template <class T>
    void addUAVEnableVertexBuffer(UINT registerNum, const std::vector<T>& data, UINT vertexBufferRegisterNum = 0);
    /**
    * @brief 頂点バッファをセットする
    */
    void setToVertexBuffer();
    /**
    * @brief 頂点バッファをクリアする
    * @details UAVを使用するときに同じリソースが頂点バッファにセットされていると動作しないので描画終了後に必ず呼ぶ
    */
    void clearVertexBuffer();
private:
    /**
    * @brief ピクセルシェーダの作成
    * @param name シェーダファイル名
    */
    void create(const std::string& name);
private:
    PROPERTY_READONLY(Info, mInfo, Info); //!< コンピュートシェーダ情報
private:
    std::unique_ptr<ComputeShaderData> mShaderData; //!< シェーダーのデータ
    std::vector<SRV> mSRVs; //!< シェーダリソースビュー配列
    std::vector<UAV> mUAVs; //!< アンオーダードアクセスビュー配列
    std::vector<VertexBuffer> mVertexBuffers; //!< 頂点バッファ配列
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
    MY_ASSERTION(SUCCEEDED(hr), "失敗");

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    srvDesc.BufferEx.FirstElement = 0;
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.BufferEx.NumElements = desc.ByteWidth / 4;

    //NumElementsは構造体の要素数。おおよその場合4Byte変数が使われていると予想されるので4で割る
    const int numElem = desc.ByteWidth / 4;
    srvDesc.BufferEx.NumElements = numElem;

    hr = DX11InterfaceAccessor::getDevice()->CreateShaderResourceView(srv.buffer.Get(), &srvDesc, &srv.srv);
    MY_ASSERTION(SUCCEEDED(hr), "失敗");

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
    MY_ASSERTION(SUCCEEDED(hr), "失敗");
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    //NumElementsは構造体の要素数。おおよその場合4Byte変数が使われていると予想されるので4で割る
    const int numElem = desc.ByteWidth / 4;
    uavDesc.Buffer.NumElements = numElem;

    hr = DX11InterfaceAccessor::getDevice()->CreateUnorderedAccessView(uav.buffer.Get(), &uavDesc, &uav.uav);
    MY_ASSERTION(SUCCEEDED(hr), "失敗");

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
    MY_ASSERTION(SUCCEEDED(hr), "失敗");
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    //NumElementsは構造体の要素数。おおよその場合4Byte変数が使われていると予想されるので4で割る
    const int numElem = desc.ByteWidth / 4;
    uavDesc.Buffer.NumElements = numElem;

    hr = DX11InterfaceAccessor::getDevice()->CreateUnorderedAccessView(uav.buffer.Get(), &uavDesc, &uav.uav);
    MY_ASSERTION(SUCCEEDED(hr), "失敗");

    mUAVs.emplace_back(uav);

    mVertexBuffers.emplace_back(VertexBuffer{ vertexBufferRegisterNum,elemSize,uav.buffer });
}

} //Graphics 
} //Framework 
