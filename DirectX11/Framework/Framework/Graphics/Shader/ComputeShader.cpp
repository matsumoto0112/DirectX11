#include "ComputeShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Utility/IO/ByteReader.h"
//#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

ComputeShader::ComputeShader(const std::string& filepath, const Info& info)
    :ShaderBase(), mInfo(info) {
    //シェーダファイルの読み込み
    std::vector<BYTE> byteData = Utility::ByteReader(addExtendIfNotExist(filepath)).get();
    //シェーダファイル作成
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateComputeShader(byteData.data(), byteData.size(), nullptr, &mComputeShader));
}

ComputeShader::~ComputeShader() {
    mSRVs.clear();
    mUAVs.clear();
    mVertexBuffers.clear();
}

void ComputeShader::set() {
    DX11InterfaceAccessor::getContext()->CSSetShader(mComputeShader.Get(), nullptr, 0);

    for (auto&& srv : mSRVs) {
        DX11InterfaceAccessor::getContext()->CSSetShaderResources(srv.registerNum, 1, srv.srv.GetAddressOf());
    }

    for (auto&& uav : mUAVs) {
        DX11InterfaceAccessor::getContext()->CSSetUnorderedAccessViews(uav.registerNum, 1, uav.uav.GetAddressOf(), nullptr);
    }

    DX11InterfaceAccessor::getContext()->Dispatch(mInfo.dispatchX, mInfo.dispatchY, mInfo.dispatchZ);

    //コンテキストのデータをきれいにする
    DX11InterfaceAccessor::getContext()->CSSetShader(nullptr, nullptr, 0);

    ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
    for (auto&& srv : mSRVs) {
        DX11InterfaceAccessor::getContext()->CSSetShaderResources(srv.registerNum, 1, nullSRV);
    }

    ID3D11UnorderedAccessView* nullUAV[1] = { nullptr };
    for (auto&& uav : mUAVs) {
        DX11InterfaceAccessor::getContext()->CSSetUnorderedAccessViews(uav.registerNum, 1, nullUAV, nullptr);
    }
}

void ComputeShader::setToVertexBuffer() {
    UINT offset = 0;
    for (auto&& buf : mVertexBuffers) {
        DX11InterfaceAccessor::getContext()->IASetVertexBuffers(buf.registerNum, 1, buf.buffer.GetAddressOf(), &buf.stride, &offset);
    }
}

void ComputeShader::clearVertexBuffer() {
    ID3D11Buffer* nullBuffer[1] = { nullptr };
    UINT nullStride = 0;
    UINT offset = 0;
    for (auto&& buf : mVertexBuffers) {
        DX11InterfaceAccessor::getContext()->IASetVertexBuffers(buf.registerNum, 1, nullBuffer, &nullStride, &offset);
    }
}

} //Graphics 
} //Framework 
