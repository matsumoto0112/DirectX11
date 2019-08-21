#include "TextureString.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/String/TextureChar.h"
#include "Framework/Math/Vector2.h"

namespace Framework {
namespace Graphics {

TextureString::TextureString(const std::string& str,
    int fontSize, const std::string& font)
    : mStr(str), mFontSize(fontSize),
    mFont(font), mPosition(Math::Vector2(0.0f, 0.0f)) {
    create();
}

TextureString::~TextureString() {
    mTextureChars.clear();
}

void TextureString::setPosition(const Math::Vector2& position) {
    mPosition = position;
    //���������������炵�Ĕz�u
    mTextureChars[0]->setPosition(position);
    for (int i = 1; i < (int)mTextureChars.size(); i++) {
        mTextureChars[i]->setPosition(mTextureChars[i - 1]->getRightPosition());
    }
}

const Math::Vector2& TextureString::getPosition() const {
    return mPosition;
}

void TextureString::setString(const std::string& str) {
    //�ς��Ȃ��̂ł���Ή������Ȃ�
    if (mStr == str)return;
    mStr = str;
    //��������蒼��
    create();
}

void TextureString::setFontSize(int size) {
    //�ς��Ȃ��̂ł���Ή������Ȃ�
    if (mFontSize == size)return;
    mFontSize = size;
    //��������蒼��
    create();
}

void TextureString::setFont(const std::string& font) {
    //�ς��Ȃ��̂ł���Ή������Ȃ�
    if (mFont == font)return;
    mFont = font;
    //��������蒼��
    create();
}

void TextureString::draw() {
    for (auto&& c : mTextureChars) {
        c->draw();
    }
}

void TextureString::setZOrder(float z) {
    for (auto&& c : mTextureChars) {
        c->setZOrder(z);
    }
}

float TextureString::getZOrder() const {
    if (mTextureChars.size() == 0) {
        return 0.0f;
    }
    return mTextureChars[0]->getZOrder();
}

void TextureString::create() {
    using Vec2 = Math::Vector2;
    const int size = mStr.length();
    //������̓��͂��Ȃ���΍쐬���Ȃ�
    if (size == 0)return;
    //�����̃N���A
    mTextureChars.clear();
    //�܂��͈ꕶ���ڂ��쐬
    std::unique_ptr<TextureChar> p = std::make_unique<TextureChar>(mStr.substr(0, 1).c_str(), mFontSize, mFont);
    p->setPosition(mPosition);
    mTextureChars.emplace_back(std::move(p));
    //2�����ڂ���͑O�̕����̍��W���炸�炵���ꏊ�ɐ���
    for (int i = 1; i < size; i++) {
        p = std::make_unique<TextureChar>(mStr.substr(i, 1).c_str(), mFontSize, mFont);
        p->setPosition(Vec2(mTextureChars.at(i - 1)->getRightPositionX(), 0));
        mTextureChars.emplace_back(std::move(p));
    }
}

} //Graphics
} //Framework 
