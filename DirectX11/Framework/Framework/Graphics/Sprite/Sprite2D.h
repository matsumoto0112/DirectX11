#pragma once

#include <memory>
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Renderer/IDrawable.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Math/Rect.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class Effect;
class Texture;

/**
* @enum PivotBase
* @brief ピボットを設定するときの基準
*/
enum class PivotBase {
    Local, //!< 自分を基準とした百分率
    Screen, //!< スクリーン座標を基準とする
};

/**
* @class Sprite2D
* @brief 2Dスプライト描画
*/
class Sprite2D : public IDrawable {
protected:
    using Rect = Math::Rect;
protected:
    Sprite2D();
public:
    /**
    * @brief コンストラクタ
    */
    Sprite2D(std::shared_ptr<Texture> texture);
    /**
    * @brief デストラクタ
    */
    virtual ~Sprite2D();
    /**
    * @brief 描画する
    */
    virtual void draw() override;
    /**
    * @brief ピボットの設定
    * @param pivot ピボットの場所
    * @param base 何を基準に設定するか
    * @detail Local:pivotを0～1で決定する。(0,0)で画像の左上、(1,1)で画像の右下に設定
              Screen:スクリーン座標をもとに決定する。(0,0)で画面の左上、(ScreenSize)で画面の右下
    */
    void setPivot(const Math::Vector2& pivot, PivotBase base = PivotBase::Local);
    /**
    * @brief ピボットの取得
    * @param base 返すピボットの基準
    * @detail Local:(0,0)で画像の左上、(1,1)で画像の右下を表す
              Screen:(0,0)で画面の左上、(ScreenSize)で画面の右下
    */
    Math::Vector2 getPivot(PivotBase base) const;
    /**
    * @brief アルファ値の設定
    * @param alpha アルファ値(0.0～1.0)
    */
    void setAlpha(float alpha);
    /**
    * @brief アルファ値の取得
    * @return 現在のアルファ値(0.0～1.0)
    */
    float getAlpha() const;
    /**
    * @brief モデル変換行列
    * @return モデル変換行列を返す(scale * rotate * translate)
    */
    Math::Matrix4x4 getModelMatrix() const;
    /**
    * @brief テクスチャデータの取得
    */
    Texture* getTexture() const;
    /**
    * @brief テクスチャの設定
    * @param texture 新しいテクスチャデータ
    * @param resize 新しい画像にスプライトの大きさを合わせるかどうか
    */
    void setTexture(std::shared_ptr<Texture> texture, bool resize);
protected:
    std::shared_ptr<Texture> mTexture;
protected:
    PROPERTY(Math::Vector2, mPosition, Position);
    PROPERTY(float, mZOrder, ZOrder);
    PROPERTY(float, mRotate, Rotate);
    PROPERTY(Math::Vector2, mScale, Scale);
    PROPERTY(Math::Vector2, mContentSize, ContentSize);
    PROPERTY(Color4, mColor, Color);
    PROPERTY(Rect, mSrcRect, SrcRect);
protected:
    Math::Vector2 mPivot;
};
} //Graphics 
} //Framework 
