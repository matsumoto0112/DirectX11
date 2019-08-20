#pragma once

#include <memory>
#include "Math/Rect.h"
#include "Graphics/Color4.h"
#include "Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {
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
class Sprite2D {
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
    virtual void draw();
    /**
    * @brief 座標の設定
    */
    void setPosition(const Math::Vector2& position);
    /**
    * @brief 座標の取得
    */
    const Math::Vector2& getPosition() const;
    void setZOrder(float z);
    float getZOrder() const;
    /**
    * @brief 回転の設定
    */
    void setRotate(float rotate);
    /**
    * @brief 回転の取得
    */
    float getRotate() const;
    /**
    * @brief スケーリングの設定
    */
    void setScale(const Math::Vector2& scale);
    /**
    * @brief スケーリングの取得
    */
    const Math::Vector2& getScale() const;
    /**
    * @brief コンテンツの大きさの設定
    */
    void setContentSize(const Math::Vector2& size);
    /**
    * @brief コンテンツの大きさの取得
    */
    const Math::Vector2& getContentSize() const;
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
    * @brief 色の設定
    */
    void setColor(const Color4& color);
    /**
    * @brief 色の取得
    */
    const Color4& getColor() const;
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
    * @brief テクスチャの矩形の設定
    * @param r 矩形情報
    * @detail r.left uvの左座標(0～1)
              r.top uvの上座標(0～1)
              r.width uvの幅(0～1)
              r.height uvの高さ(0～1)
              を設定する
    */
    void setSrcRect(const Rect& r);
    /**
    * @brief テクスチャの矩形の取得
    * @return 矩形情報を返す
    * @detail r.left uvの左座標(0～1)
              r.top uvの上座標(0～1)
              r.width uvの幅(0～1)
              r.height uvの高さ(0～1)
              を取得する
    */
    const Rect& getSrcRect() const;
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
    void setTexture(std::shared_ptr<Texture>& texture, bool resize);
protected:
    std::shared_ptr<Texture> mTexture;
    Math::Vector2 mPosition;
    float mZOrder;
    float mRotate;
    Math::Vector2 mScale;
    Math::Vector2 mContentSize;
    Math::Vector2 mPivot;
    Color4 mColor;
    Rect mSrcRect;
};
} //Graphics 
} //Framework 
