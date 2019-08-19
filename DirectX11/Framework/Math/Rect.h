#pragma once

#include "Math/Vector2.h"
namespace Framework {
namespace Math {

/**
* @class Rect
* @brief 矩形クラス
*/
class Rect {
public:
    /**
    * @brief デフォルトコンストラクタ
    */
    Rect();
    /**
    * @brief コンストラクタ
    * @param x x座標
    * @param y y座標
    * @param width 幅
    * @param height 高さ
    */
    Rect(float x, float y, float width, float height);
    /**
    * @brief コンストラクタ
    * @param center 中心座標
    * @param size 大きさ
    */
    Rect(const Vector2& center, const Vector2& size);
    /**
    * @brief デストラクタ
    */
    ~Rect();
    /**
    * @brief x座標を取得
    */
    float getX() const;
    /**
    * @brief x座標を設定
    */
    void setX(float x);
    /**
    * @brief y座標を取得
    */
    float getY() const;
    /**
    * @brief y座標を設定
    */
    void setY(float y);
    /**
    * @brief 座標を取得
    */
    Vector2 getPosition() const;
    /**
    * @brief 座標を設定
    */
    void setPosition(const Vector2& position);
    /**
    * @brief 座標を設定
    */
    void setPosition(float x, float y);
    /**
    * @brief 幅を取得
    */
    float getWidth() const;
    /**
    * @brief 幅を設定
    */
    void setWidth(float width);
    /**
    * @brief 高さを取得
    */
    float getHeight() const;
    /**
    * @brief 高さを設定
    */
    void setHeight(float height);
    /**
    * @brief 幅と高さを取得
    */
    Vector2 getSize() const;
    /**
    * @brief 幅と高さを設定
    */
    void setSize(const Vector2& size);
    /**
    * @brief 幅と高さを設定
    */
    void setSize(float width, float height);
    /**
    * @brief 最小x座標を取得
    */
    float getXMin() const;
    /**
    * @brief 最小x座標を設定
    */
    void setXMin(float xmin);
    /**
    * @brief 最大x座標を取得
    */
    float getXMax() const;
    /**
    * @brief 最大x座標を設定
    */
    void setXMax(float xmax);
    /**
    * @brief 最小y座標を取得
    */
    float getYMin() const;
    /**
    * @brief 最小y座標を設定
    */
    void setYMin(float ymin);
    /**
    * @brief 最大y座標を取得
    */
    float getYMax() const;
    /**
    * @brief 最大y座標を設定
    */
    void setYMax(float ymax);
    /**
    * @brief 最小座標を取得
    */
    Vector2 getMin() const;
    /**
    * @brief 最小座標を設定
    */
    void setMin(const Vector2& min);
    /**
    * @brief 最小座標を設定
    */
    void setMin(float xmin, float ymin);
    /**
    * @brief 最大座標を取得
    */
    Vector2 getMax() const;
    /**
    * @brief 最大座標を設定
    */
    void setMax(const Vector2& max);
    /**
    * @brief 最大座標を設定
    */
    void setMax(float xmax, float ymax);
    /**
    * @brief 中心座標を取得
    */
    Vector2 getCenter() const;
    /**
    * @brief 点を含んでいるか
    * @param point 点の座標
    * @return 含んでいたらtrue
    */
    bool contains(const Vector2& point) const;
    /**
    * @brief 別の矩形と重なっているか
    * @param rect 調べる矩形
    * @return 重なっていたらtrue
    */
    bool intersects(const Rect& rect) const;
private:
    float x; //!< x座標
    float y; //!< y座標
    float width; //!< 幅
    float height; //!< 高さ
};

} //Math 
} //Framework 