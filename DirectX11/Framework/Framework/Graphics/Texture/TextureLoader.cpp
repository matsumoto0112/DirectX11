#include "TextureLoader.h"
#include <vector>
#include <atlstr.h>
#include "Framework/Graphics/Shader/ShaderResourceView.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

TextureLoader::TextureLoader() {
    //イメージファクトリ作成
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory,
        nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mFactory));
    MY_ASSERTION(SUCCEEDED(hr), "イメージファクトリ作成失敗");

    //フォーマット変換器作成
    hr = mFactory->CreateFormatConverter(&mConverter);
    MY_ASSERTION(SUCCEEDED(hr), "FormatConverter作成失敗");

    //テクスチャデスク作成
    ZeroMemory(&mTexture2DDesc, sizeof(mTexture2DDesc));
    mTexture2DDesc.MipLevels = 1;
    mTexture2DDesc.ArraySize = 1;
    mTexture2DDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    mTexture2DDesc.SampleDesc.Count = 1;
    mTexture2DDesc.SampleDesc.Quality = 0;
    mTexture2DDesc.Usage = D3D11_USAGE_DEFAULT;
    mTexture2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    mTexture2DDesc.CPUAccessFlags = 0;
    mTexture2DDesc.MiscFlags = 0;
    ZeroMemory(&mSRVDesc, sizeof(mSRVDesc));
    mSRVDesc.Format = mTexture2DDesc.Format;
    mSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    mSRVDesc.Texture2D.MipLevels = mTexture2DDesc.MipLevels;
}

TextureLoader::~TextureLoader() {}

std::unique_ptr<Texture> TextureLoader::load(const std::string& filepath) {
    //マルチバイト文字に変換
    CStringW wPath(filepath.c_str());
    //パスからデコーダーを作成
    HRESULT hr = mFactory->CreateDecoderFromFilename(
        wPath, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &mDecoder);
    MY_ASSERTION(SUCCEEDED(hr), "デコーダー作成失敗\nファイル名は" + filepath);

    //フレームの取得
    hr = mDecoder->GetFrame(0, &mFrame);
    MY_ASSERTION(SUCCEEDED(hr), "GetFrame失敗");

    UINT width, height;
    mFrame->GetSize(&width, &height);
    //ピクセル形式を取得
    WICPixelFormatGUID pixelFormat;
    hr = mFrame->GetPixelFormat(&pixelFormat);
    MY_ASSERTION(SUCCEEDED(hr), "GetPixelFrame失敗");

    int stride = width * 4;
    int bufferSize = stride * height;
    std::vector<BYTE> buffer(bufferSize);
    //ピクセル形式が32bitRGBAでなかったら変換する
    if (pixelFormat != GUID_WICPixelFormat32bppRGBA) {
        hr = mFactory->CreateFormatConverter(&mConverter);
        MY_ASSERTION(SUCCEEDED(hr), "FormatConverter作成失敗");

        hr = mConverter->Initialize(mFrame, GUID_WICPixelFormat32bppRGBA,
            WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeCustom);
        MY_ASSERTION(SUCCEEDED(hr), "Converterの初期化失敗");

        hr = mConverter->CopyPixels(0, stride, bufferSize, buffer.data());
        MY_ASSERTION(SUCCEEDED(hr), "ピクセルデータのコピー失敗");
    }
    else {
        hr = mFrame->CopyPixels(nullptr, stride, bufferSize, buffer.data());
        MY_ASSERTION(SUCCEEDED(hr), "ピクセルデータのコピー失敗");
    }

    //テクスチャ作成
    mTexture2DDesc.Width = width;
    mTexture2DDesc.Height = height;

    D3D11_SUBRESOURCE_DATA sub;
    ZeroMemory(&sub, sizeof(sub));
    sub.pSysMem = buffer.data();
    sub.SysMemPitch = width * 4;
    sub.SysMemSlicePitch = buffer.size();

    //テクスチャ作成
    std::shared_ptr<TextureBuffer> texture2D = std::make_shared<TextureBuffer>(mTexture2DDesc, sub);
    std::shared_ptr<ShaderResourceView> srv =
        std::make_shared<ShaderResourceView>(*texture2D, mSRVDesc);

    return std::make_unique<Texture>(texture2D, srv, width, height);
}
} //Graphics 
} //Framework 
