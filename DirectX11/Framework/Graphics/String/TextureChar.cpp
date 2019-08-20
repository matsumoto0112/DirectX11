#include "TextureChar.h"
#include <atlstr.h>
#include "Graphics/DirectX11GraphicsDevice.h"
#include "Graphics/Shader/ShaderResourceView.h"
#include "Graphics/Sprite/Sprite2D.h"
#include "Graphics/Texture/Texture.h"
#include "Graphics/Texture/TextureBuffer.h"
#include "Utility/Wrap/DirectX.h"
#include "Utility/Debug.h"

namespace Framework {
namespace Graphics {

TextureChar::TextureChar(const char* c, int fontSize, const std::string& font)
    :Sprite2D() {
    LOGFONT lf = {
        fontSize, //高さ
        0, // 幅
        0, //文字送りの方向とX軸との角度
        0, //ベースラインとX軸との角度
        0, //フォントの太さ
        0, //イタリック体指定
        0, //下線付き指定
        0, //打消し線付き指定
           SHIFTJIS_CHARSET, //キャラクタセット
           OUT_TT_ONLY_PRECIS, //出力精度
           CLIP_DEFAULT_PRECIS, //クリッピングの精度
           PROOF_QUALITY, //出力品質
           FIXED_PITCH | FF_MODERN, //ピッチとファミリ
    };
#if UNICODE
    _tcscpy_s(lf.lfFaceName, CStringW(font.c_str()));
#else
    _tcscpy_s(lf.lfFaceName, font.c_str());
#endif

    HFONT hfont = CreateFontIndirect(&lf);
    if (!hfont) {
        _ASSERT("フォント作成失敗");
    }
    //デバイスコンテキスト取得
    HDC hdc = GetDC(NULL);
    HFONT oldFont = (HFONT)SelectObject(hdc, hfont);

    UINT code = 0;
#if _UNICODE
    code = (UINT)*c;
#else
    if (IsDBCSLeadByte(*c))
        code = (BYTE)c[0] << 8 | (BYTE)c[1];
    else
        code = c[0];
#endif

    //フォントビットマップ取得
    TEXTMETRIC TM;
    GetTextMetrics(hdc, &TM);
    GLYPHMETRICS GM;
    const MAT2 mat{ { 0,1 },{ 0,0 },{ 0,0 } ,{ 0,1 } };
    DWORD size = GetGlyphOutline(
        hdc, //デバイスコンテキストハンドル 
        code, //コード番号
        GGO_GRAY4_BITMAP,  //関数が返すデータフォーマット
        &GM,  //!< 構造体ポインタ
        0,  //!< 次のバッファのサイズ
        NULL, //!< ビットマップ情報を受け取るバッファ
        &mat //!< 文字変換行列
    );
    BYTE* ptr = new BYTE[size];
    GetGlyphOutline(
        hdc, //デバイスコンテキストハンドル 
        code, //コード番号
        GGO_GRAY4_BITMAP,  //関数が返すデータフォーマット
        &GM,  //!< 構造体ポインタ
        size,  //!< 次のバッファのサイズ
        ptr, //!< ビットマップ情報を受け取るバッファ
        &mat //!< 文字変換行列
    );
    //デバイスコンテキストとフォントハンドルの解放
    SelectObject(hdc, oldFont);
    DeleteObject(hfont);
    ReleaseDC(NULL, hdc);

    //テクスチャ作成
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = GM.gmCellIncX;
    desc.Height = TM.tmHeight;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DYNAMIC; //動的（書き込みするための必須条件）
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE; //シェーダーリソースとして扱う
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPUからアクセスして書き込みを許可する
    std::shared_ptr<TextureBuffer> tex = std::make_shared<TextureBuffer>(desc);

    D3D11_MAPPED_SUBRESOURCE hMappedResource;
    HRESULT hr = Utility::getContext()->Map(
        tex->getBuffer().Get(),
        0,
        D3D11_MAP_WRITE_DISCARD,
        0,
        &hMappedResource);
    _ASSERT_EXPR(SUCCEEDED(hr), "テクスチャマップ作成失敗");
    BYTE* pBits = (BYTE*)hMappedResource.pData;

    //フォント情報の書き込み
    mOffset = IntVec2(GM.gmptGlyphOrigin.x, TM.tmAscent - GM.gmptGlyphOrigin.y); //書き出し位置
    mBmpSize = IntVec2(GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4, GM.gmBlackBoxY);
    mMargin = IntVec2(GM.gmCellIncX - GM.gmptGlyphOrigin.x - GM.gmBlackBoxX, TM.tmHeight - GM.gmptGlyphOrigin.y - GM.gmBlackBoxY);

    int level = 17; //α値の段階 GGO_GRAY4_BITMAPなので17段階
    DWORD Alpha, Color;
    FillMemory(pBits, hMappedResource.RowPitch * TM.tmHeight, 0);
    //iOfsまでは透明な部分 iOfs+iMmpからも透明な部分なため無視
    for (int y = mOffset.y; y < mOffset.y + mBmpSize.y; y++) {
        for (int x = mOffset.x; x < mOffset.x + mBmpSize.x; x++) {
            Alpha = (255 * ptr[x - mOffset.x + mBmpSize.x * (y - mOffset.y)]) / (level - 1);
            Color = 0x00ffffff | (Alpha << 24);
            memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &Color, sizeof(DWORD));
        }
    }
    Utility::getContext()->Unmap(tex->getBuffer().Get(), 0);

    // ShaderResourceViewの情報を作成する
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = desc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;

    std::shared_ptr<ShaderResourceView> srv =
        std::make_unique<ShaderResourceView>(*tex, srvDesc);

    mTexture = std::make_shared<Texture>(tex, srv, GM.gmCellIncX, TM.tmHeight);
    mContentSize = Math::Vector2((float)mTexture->getWidth(), (float)mTexture->getHeight());
    delete[] ptr;
}

TextureChar::~TextureChar() {}

void TextureChar::draw() {
    Sprite2D::draw();
}

float TextureChar::getDisplayWidth() const {
    return (mOffset.x + mBmpSize.x) * mScale.x;
}

float TextureChar::getRightPositionX() const {
    return (mOffset.x + mBmpSize.x + mMargin.x) * mScale.x + mPosition.x;
}

Math::Vector2 TextureChar::getRightPosition() const {
    return Math::Vector2(getRightPositionX(), mPosition.y);
}

} //Graphics
} //Framework 

