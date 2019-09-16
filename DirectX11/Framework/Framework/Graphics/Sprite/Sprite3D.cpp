#include "Sprite3D.h"
#include "Framework/Graphics/Sprite/SpriteRenderer.h"

namespace Framework {
namespace Graphics {

Sprite3D::Sprite3D(std::shared_ptr<Texture> texture)
    :mTexture(texture),
    mPosition(Math::Vector3::ZERO),
    mScale(Math::Vector3(1.0f, 1.0f, 1.0f)),
    mContentSize(static_cast<float>(texture->getWidth()), static_cast<float>(texture->getHeight())),
    mColor(Color4::WHITE),
    mSrcRect(Math::Rect(0.0f, 0.0f, 1.0f, 1.0f)) {}

Sprite3D::~Sprite3D() {}

Math::Matrix4x4 Sprite3D::createBillboardMatrix(const Math::Matrix4x4& invView) const {
    Math::Matrix4x4 scale(Math::Matrix4x4::createScale(mScale));
    Math::Matrix4x4 rotate(Math::Matrix4x4::createRotationZ(0.0f));
    Math::Matrix4x4 world(Math::Matrix4x4::createTranslate(mPosition));

    world.m[3][0] -= 0.5f * mScale.x;
    world.m[3][1] -= 0.5f * mScale.y;
    world = invView * scale * rotate * world;
    return world;
}

void Sprite3D::setAlpha(float alpha) {
    mColor.a = alpha;
}

float Sprite3D::getAlpha() const {
    return mColor.a;
}


} //Graphics 
} //Framework 
