#pragma once

#include <array>
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Matrix3x3.h"
#include "Framework/Math/MathUtility.h"
namespace Framework {
namespace Math {

/**
* @class Circle2D
* @brief 円
*/
class Circle2D {
public:
    /**
    * @brief デフォルトコンストラクタ
    */
    Circle2D() {};
    /**
    * @brief コンストラクタ
    * @param center 中心座標
    * @param radius 半径
    */
    Circle2D(const Vector2& center, float radius)
        :center(center), radius(radius) {};
    /**
    * @brief デストラクタ
    */
    ~Circle2D() {};
public:
    Vector2 center; //!< 中心座標
    float radius; //!< 半径
};

/**
* @class Line2D
* @brief 直線
*/
class Line2D {
public:
    /**
    * @brief コンストラクタ
    */
    Line2D() {};
    /**
    * @brief コンストラクタ
    * @param position 始点
    * @param direction 方向ベクトル
    */
    Line2D(const Vector2& position, const Vector2& direction)
        :position(position), direction(direction) {};
    /**
    * @brief デストラクタ
    */
    ~Line2D() {};

    /**
    * @brief 正規化された方向ベクトルを取得
    */
    inline Vector2 getNormalDirection() const {
        return direction.getNormal();
    }
public:
    Vector2 position; //!< 始点
    Vector2 direction; //!< 方向ベクトル
};

using Ray2D = Line2D;

/**
* @class Segment2D
* @brief 線分
*/
class Segment2D : public Line2D {
public:
    /**
    * @brief コンストラクタ
    */
    Segment2D() :Line2D() {};
    /**
    * @brief コンストラクタ
    * @param position 始点
    * @param direction 方向ベクトル（正規化）
    * @param length 長さ
    */
    Segment2D(const Vector2& position, const Vector2& direction, float length)
        :Line2D(position, direction), length(length) {};
    /**
    * @brief コンストラクタ
    * @param start 始点
    * @param end 終点
    */
    Segment2D(const Vector2& start, const Vector2& end)
        :Segment2D(start, (end - start).getNormal(), (end - start).length()) {}
    /**
    * @brief 終点の取得
    */
    Vector2 getEndPosition() const {
        return position + direction * length;
    };
public:
    float length; //!< 線分の長さ
};

/**
* @class AABB2D
* @brief 矩形
*/
class AABB2D {
public:
    /**
    * @brief コンストラクタ
    */
    AABB2D() {}
    /**
    * @brief コンストラクタ
    * @param position 中心座標
    * @param size 幅と高さ
    */
    AABB2D(const Vector2& position, const Vector2& size)
        :position(position), size(size) {}
    /**
    * @brief コンストラクタ
    * @param left 左座標(x)
    * @param top 上座標(y)
    * @param right 右座標(x)
    * @param bottom 下座標(y)
    */
    AABB2D(float left, float top, float right, float bottom)
        :AABB2D(Vector2((left + right) * 0.5f, (top + bottom) * 0.5f),
            Vector2(right - left, bottom - top)) {}

    /**
    * @brief 左
    */
    inline float left() const {
        return position.x - size.x * 0.5f;
    }
    /**
    * @brief 右
    */
    inline float right() const {
        return position.x + size.x * 0.5f;
    }
    /**
    * @brief 上
    */
    inline float top() const {
        return position.y - size.y * 0.5f;
    }
    /**
    * @brief 下
    */
    inline float bottom() const {
        return position.y + size.y * 0.5f;
    }
public:
    Vector2 position; //!< 中心座標
    Vector2 size; //!< 幅と高さ
};

/**
* @class OBB2D
* @brief 2D有向境界ボックス
*/
class OBB2D {
public:
    /**
    * @brief コンストラクタ
    */
    OBB2D() {}
    /**
    * @brief コンストラクタ
    * @param position 中心座標
    * @param size 各軸の大きさ
    * @param rotate 回転（度）
    */
    OBB2D(const Vector2& position, const Vector2& size, float rotate)
        :position(position), size(size), rotate(rotate) {}

    /**
    * @brief AABBに変換する
    */
    static AABB2D toAABB2D(const OBB2D& obb) {
        std::array<Vector2, 4> a = obb.getVertices();
        float left = MathUtility::mymin({ a[0].x,a[1].x,a[2].x, a[3].x });
        float top = MathUtility::mymin({ a[0].y,a[1].y, a[2].y, a[3].y });
        float right = MathUtility::mymax({ a[0].x, a[1].x, a[2].x, a[3].x });
        float bottom = MathUtility::mymax({ a[0].y, a[1].y, a[2].y, a[3].y });
        return AABB2D(left, top, right, bottom);
    }

    /**
    * @brief 回転を無視したAABBに変換する
    */
    static AABB2D toAABB2DIgnoreRotate(const OBB2D& obb) {
        return AABB2D(obb.position, obb.size);
    }

    /**
    * @brief 頂点と頂点を結ぶ4直線を取得する
    */
    std::array<Vector2, 4> getVertices() const {
        const Vector2 halfSize = size * 0.5f;
        const float left = position.x - halfSize.x;
        const float right = position.x + halfSize.x;
        const float top = position.y - halfSize.y;
        const float bottom = position.y + halfSize.y;
        Matrix3x3 rotateMat = Matrix3x3::createTranslate(-position) *
            Matrix3x3::createRotate(-rotate) * Matrix3x3::createTranslate(position);
        std::array<Vector2, 4> res;
        res[0] = Vector2(left, top) * rotateMat;
        res[1] = Vector2(left, bottom) * rotateMat;
        res[2] = Vector2(right, bottom) * rotateMat;
        res[3] = Vector2(right, top) * rotateMat;
        return res;
    }
public:
    Vector2 position; //!< 中心座標
    Vector2 size; //!< 幅と高さ
    float rotate; //!< 回転
};

/**
* @class Capsule2D
* @brief カプセル
*/
class Capsule2D {
public:
    /**
    * @brief コンストラクタ
    */
    Capsule2D() {};
    /**
    * @brief コンストラクタ
    * @param segment 中心線分
    * @param radius 半径
    */
    Capsule2D(const Segment2D& segment, float radius)
        :segment(segment), radius(radius) {};
public:
    Segment2D segment; //!< 中心線分
    float radius; //!< 半径
};

} //Math 
} //Framework 