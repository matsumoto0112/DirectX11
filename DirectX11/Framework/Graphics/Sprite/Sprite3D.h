#pragma once
#include "Graphics/Color4.h"
#include "Graphics/Texture/Texture.h"
#include "Math/Matrix4x4.h"
#include "Math/Rect.h"

namespace Framework {
namespace Graphics {

/**
* @class Sprite3D
* @brief 3Dビルボードスプライト
*/
class Sprite3D {
public:
    /**
    * @brief コンストラクタ
    * @param texture 使用するテクスチャ
    */
    Sprite3D(std::shared_ptr<Texture> texture);
    /**
    * @brief デストラクタ
    */
    ~Sprite3D();
    std::shared_ptr<Texture> getTexture() const { return mTexture; };
    void setTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
    /**
    * @brief 座標の取得
    */
    const Math::Vector3& getPosition() const { return mPosition; }
    /**
    * @brief 座標の設定
    */
    void setPosition(const Math::Vector3& position) { mPosition = position; }
    /**
    * @brief 大きさの取得
    */
    const Math::Vector3& getScale() const { return mScale; }
    /**
    * @brief 大きさの設定
    */
    void setScale(const Math::Vector3& scale) { mScale = scale; }
    const Color4& getColor() const { return mColor; }
    void setColor(const Color4& color) { mColor = color; }
    const Math::Rect& getSrcRect() const { return mSrcRect; }
    void setSrcRect(const Math::Rect& rect) { mSrcRect = rect; }
    /**
    * @brief 描画
    */
    void draw();

    Math::Matrix4x4 createBillboardMatrix(const Math::Matrix4x4& invView) const;
private:
    std::shared_ptr<Texture> mTexture;
    Math::Vector3 mPosition;
    Math::Vector3 mScale;
    Math::Vector2 mContentSize;
    Color4 mColor;
    Math::Rect mSrcRect;
};

} //Graphics 
} //Framework 
