#include "Sprite2D.h"
#include "Graphics/Texture/Texture.h"
#include "Graphics/Sprite/SpriteRenderer.h"

namespace Framework {
namespace Graphics {

Sprite2D::Sprite2D()
    :mTexture(nullptr),
    mPosition(0, 0),
    mZOrder(0.0f),
    mRotate(0.0f),
    mScale(1, 1),
    mContentSize(Math::Vector2(0, 0)),
    mPivot(0, 0),
    mColor(1.0f, 1.0f, 1.0f, 1.0f),
    mSrcRect(0.0f, 0.0f, 1.0f, 1.0f) {}

Sprite2D::Sprite2D(std::shared_ptr<Texture> texture)
    : mTexture(texture),
    mPosition(0, 0),
    mZOrder(0.0f),
    mRotate(0.0f),
    mScale(1.0f, 1.0f),
    mContentSize((float)texture->getWidth(), (float)texture->getHeight()),
    mPivot(0.0f, 0.0f),
    mColor(1.0f, 1.0f, 1.0f, 1.0f),
    mSrcRect(0.0f, 0.0f, 1.0f, 1.0f) {}

Sprite2D::~Sprite2D() {}

void Sprite2D::draw() {
    SpriteRenderer::getInstance().draw(this);
}

void Sprite2D::setPosition(const Math::Vector2& position) {
    mPosition = position;
}

const Math::Vector2& Sprite2D::getPosition() const {
    return mPosition;
}

void Sprite2D::setZOrder(float z) {
    mZOrder = z;
}

float Sprite2D::getZOrder() const {
    return mZOrder;
}

void Sprite2D::setRotate(float rotate) {
    mRotate = rotate;
}

float Sprite2D::getRotate() const {
    return mRotate;
}

void Sprite2D::setScale(const Math::Vector2& scale) {
    mScale = scale;
}

const Math::Vector2& Sprite2D::getScale() const {
    return mScale;
}

void Sprite2D::setContentSize(const Math::Vector2& size) {
    mContentSize = size;
}

const Math::Vector2& Sprite2D::getContentSize() const {
    return mContentSize;
}

void Sprite2D::setPivot(const Math::Vector2& pivot, PivotBase base) {
    //自分を基準とする場合
    if (base == PivotBase::Local) {
        mPivot = Math::Vector2(mContentSize.x * pivot.x, mContentSize.y * pivot.y);
    }
    //スクリーン座標を基準とする場合
    else {
        mPivot = pivot - mPosition;
    }
}

Math::Vector2 Sprite2D::getPivot(PivotBase base) const {
    if (base == PivotBase::Local) {
        return Math::Vector2(mPivot.x / mContentSize.x, mPivot.y / mContentSize.y);
    }
    else {
        return mPivot + mPosition;
    }
}

void Sprite2D::setColor(const Color4& color) {
    mColor = color;
}

const Color4& Sprite2D::getColor() const {
    return mColor;
}

void Sprite2D::setAlpha(float alpha) {
    mColor.a = alpha;
}

float Sprite2D::getAlpha() const {
    return mColor.a;
}

void Sprite2D::setSrcRect(const Rect& r) {
    mSrcRect = r;
}

const Math::Rect& Sprite2D::getSrcRect() const {
    return mSrcRect;
}

Math::Matrix4x4 Sprite2D::getModelMatrix() const {
    Math::Matrix4x4 world(Math::Matrix4x4::createScale(mContentSize.x, mContentSize.y, 1.0f));
    Math::Matrix4x4 scale(Math::Matrix4x4::createScale(mScale.x, mScale.y, 1.0f));
    Math::Matrix4x4 rotate(Math::Matrix4x4::createRotationZ(mRotate));
    world.m[3][0] -= mPivot.x;
    world.m[3][1] -= mPivot.y;
    world = world * scale * rotate;
    world.m[3][0] += mPosition.x + mPivot.x;
    world.m[3][1] += mPosition.y + mPivot.y;
    world.m[3][2] = mZOrder;
    return world;
}

Texture* Sprite2D::getTexture() const {
    return mTexture.get();
}

void Sprite2D::setTexture(std::shared_ptr<Texture>& texture, bool resize) {
    mTexture = texture;
    if (resize) {
        setScale(Math::Vector2(
            static_cast<float>(mTexture->getWidth()),
            static_cast<float>(mTexture->getHeight())
        ));
    }
}

} //Graphics 
} //Framework 
