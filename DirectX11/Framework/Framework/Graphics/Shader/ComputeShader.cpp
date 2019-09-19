#include "ComputeShader.h"
#include "Framework/Define/Path.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Utility/IO/ByteReader.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

ComputeShader::ComputeShader(const std::string& filename, const Info& info)
    :ShaderBase(), mShaderData(std::make_unique<ComputeShaderData>()), mInfo(info) {
    create(filename);
}

ComputeShader::~ComputeShader() {
    mSRVs.clear();
    mUAVs.clear();
    mVertexBuffers.clear();
}

void ComputeShader::set() {
    Utility::getContext()->CSSetShader(mShaderData->mComputeShader.Get(), nullptr, 0);

    for (auto&& srv : mSRVs) {
        Utility::getContext()->CSSetShaderResources(srv.registerNum, 1, srv.srv.GetAddressOf());
    }

    for (auto&& uav : mUAVs) {
        Utility::getContext()->CSSetUnorderedAccessViews(uav.registerNum, 1, uav.uav.GetAddressOf(), nullptr);
    }

    Utility::getContext()->Dispatch(mInfo.dispatchX, mInfo.dispatchY, mInfo.dispatchZ);

    //コンテキストのデータをきれいにする
    Utility::getContext()->CSSetShader(nullptr, nullptr, 0);

    ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
    for (auto&& srv : mSRVs) {
        Utility::getContext()->CSSetShaderResources(srv.registerNum, 1, nullSRV);
    }

    ID3D11UnorderedAccessView* nullUAV[1] = { nullptr };
    for (auto&& uav : mUAVs) {
        Utility::getContext()->CSSetUnorderedAccessViews(uav.registerNum, 1, nullUAV, nullptr);
    }
}

void ComputeShader::setToVertexBuffer() {
    UINT offset = 0;
    for (auto&& buf : mVertexBuffers) {
        Utility::getContext()->IASetVertexBuffers(buf.registerNum, 1, buf.buffer.GetAddressOf(), &buf.stride, &offset);
    }
}

void ComputeShader::clearVertexBuffer() {
    ID3D11Buffer* nullBuffer[1] = { nullptr };
    UINT nullStride = 0;
    UINT offset = 0;
    for (auto&& buf : mVertexBuffers) {
        Utility::getContext()->IASetVertexBuffers(buf.registerNum, 1, nullBuffer, &nullStride, &offset);
    }
}

void ComputeShader::create(const std::string& name) {
    //ファイルパスの作成
    const std::string filename = Define::Path::getInstance().shader() + name + ".cso";
    //シェーダファイルの読み込み
    std::vector<BYTE> byteData = Utility::ByteReader(filename).get();
    //シェーダファイル作成
    Utility::getDevice()->CreateComputeShader(byteData.data(), byteData.size(), nullptr, &mShaderData->mComputeShader);
}

} //Graphics 
} //Framework 
