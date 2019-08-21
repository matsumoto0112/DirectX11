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
    //文字を少しずつずらして配置
    mTextureChars[0]->setPosition(position);
    for (int i = 1; i < (int)mTextureChars.size(); i++) {
        mTextureChars[i]->setPosition(mTextureChars[i - 1]->getRightPosition());
    }
}

const Math::Vector2& TextureString::getPosition() const {
    return mPosition;
}

void TextureString::setString(const std::string& str) {
    //変わらないのであれば何もしない
    if (mStr == str)return;
    mStr = str;
    //文字を作り直す
    create();
}

void TextureString::setFontSize(int size) {
    //変わらないのであれば何もしない
    if (mFontSize == size)return;
    mFontSize = size;
    //文字を作り直す
    create();
}

void TextureString::setFont(const std::string& font) {
    //変わらないのであれば何もしない
    if (mFont == font)return;
    mFont = font;
    //文字を作り直す
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
    //文字列の入力がなければ作成しない
    if (size == 0)return;
    //文字のクリア
    mTextureChars.clear();
    //まずは一文字目を作成
    std::unique_ptr<TextureChar> p = std::make_unique<TextureChar>(mStr.substr(0, 1).c_str(), mFontSize, mFont);
    p->setPosition(mPosition);
    mTextureChars.emplace_back(std::move(p));
    //2文字目からは前の文字の座標からずらした場所に生成
    for (int i = 1; i < size; i++) {
        p = std::make_unique<TextureChar>(mStr.substr(i, 1).c_str(), mFontSize, mFont);
        p->setPosition(Vec2(mTextureChars.at(i - 1)->getRightPositionX(), 0));
        mTextureChars.emplace_back(std::move(p));
    }
}

} //Graphics
} //Framework 
