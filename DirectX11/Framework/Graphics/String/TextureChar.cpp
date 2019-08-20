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
        fontSize, //����
        0, // ��
        0, //��������̕�����X���Ƃ̊p�x
        0, //�x�[�X���C����X���Ƃ̊p�x
        0, //�t�H���g�̑���
        0, //�C�^���b�N�̎w��
        0, //�����t���w��
        0, //�ŏ������t���w��
           SHIFTJIS_CHARSET, //�L�����N�^�Z�b�g
           OUT_TT_ONLY_PRECIS, //�o�͐��x
           CLIP_DEFAULT_PRECIS, //�N���b�s���O�̐��x
           PROOF_QUALITY, //�o�͕i��
           FIXED_PITCH | FF_MODERN, //�s�b�`�ƃt�@�~��
    };
#if UNICODE
    _tcscpy_s(lf.lfFaceName, CStringW(font.c_str()));
#else
    _tcscpy_s(lf.lfFaceName, font.c_str());
#endif

    HFONT hfont = CreateFontIndirect(&lf);
    if (!hfont) {
        _ASSERT("�t�H���g�쐬���s");
    }
    //�f�o�C�X�R���e�L�X�g�擾
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

    //�t�H���g�r�b�g�}�b�v�擾
    TEXTMETRIC TM;
    GetTextMetrics(hdc, &TM);
    GLYPHMETRICS GM;
    const MAT2 mat{ { 0,1 },{ 0,0 },{ 0,0 } ,{ 0,1 } };
    DWORD size = GetGlyphOutline(
        hdc, //�f�o�C�X�R���e�L�X�g�n���h�� 
        code, //�R�[�h�ԍ�
        GGO_GRAY4_BITMAP,  //�֐����Ԃ��f�[�^�t�H�[�}�b�g
        &GM,  //!< �\���̃|�C���^
        0,  //!< ���̃o�b�t�@�̃T�C�Y
        NULL, //!< �r�b�g�}�b�v�����󂯎��o�b�t�@
        &mat //!< �����ϊ��s��
    );
    BYTE* ptr = new BYTE[size];
    GetGlyphOutline(
        hdc, //�f�o�C�X�R���e�L�X�g�n���h�� 
        code, //�R�[�h�ԍ�
        GGO_GRAY4_BITMAP,  //�֐����Ԃ��f�[�^�t�H�[�}�b�g
        &GM,  //!< �\���̃|�C���^
        size,  //!< ���̃o�b�t�@�̃T�C�Y
        ptr, //!< �r�b�g�}�b�v�����󂯎��o�b�t�@
        &mat //!< �����ϊ��s��
    );
    //�f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̉��
    SelectObject(hdc, oldFont);
    DeleteObject(hfont);
    ReleaseDC(NULL, hdc);

    //�e�N�X�`���쐬
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = GM.gmCellIncX;
    desc.Height = TM.tmHeight;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DYNAMIC; //���I�i�������݂��邽�߂̕K�{�����j
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE; //�V�F�[�_�[���\�[�X�Ƃ��Ĉ���
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPU����A�N�Z�X���ď������݂�������
    std::shared_ptr<TextureBuffer> tex = std::make_shared<TextureBuffer>(desc);

    D3D11_MAPPED_SUBRESOURCE hMappedResource;
    HRESULT hr = Utility::getContext()->Map(
        tex->getBuffer().Get(),
        0,
        D3D11_MAP_WRITE_DISCARD,
        0,
        &hMappedResource);
    _ASSERT_EXPR(SUCCEEDED(hr), "�e�N�X�`���}�b�v�쐬���s");
    BYTE* pBits = (BYTE*)hMappedResource.pData;

    //�t�H���g���̏�������
    mOffset = IntVec2(GM.gmptGlyphOrigin.x, TM.tmAscent - GM.gmptGlyphOrigin.y); //�����o���ʒu
    mBmpSize = IntVec2(GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4, GM.gmBlackBoxY);
    mMargin = IntVec2(GM.gmCellIncX - GM.gmptGlyphOrigin.x - GM.gmBlackBoxX, TM.tmHeight - GM.gmptGlyphOrigin.y - GM.gmBlackBoxY);

    int level = 17; //���l�̒i�K GGO_GRAY4_BITMAP�Ȃ̂�17�i�K
    DWORD Alpha, Color;
    FillMemory(pBits, hMappedResource.RowPitch * TM.tmHeight, 0);
    //iOfs�܂ł͓����ȕ��� iOfs+iMmp����������ȕ����Ȃ��ߖ���
    for (int y = mOffset.y; y < mOffset.y + mBmpSize.y; y++) {
        for (int x = mOffset.x; x < mOffset.x + mBmpSize.x; x++) {
            Alpha = (255 * ptr[x - mOffset.x + mBmpSize.x * (y - mOffset.y)]) / (level - 1);
            Color = 0x00ffffff | (Alpha << 24);
            memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &Color, sizeof(DWORD));
        }
    }
    Utility::getContext()->Unmap(tex->getBuffer().Get(), 0);

    // ShaderResourceView�̏����쐬����
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

