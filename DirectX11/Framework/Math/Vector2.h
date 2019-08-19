#pragma once

#include <ostream>
#include "Math/MathUtility.h"
namespace Framework {
namespace Math {

class Vector3;

/**
* @class Vector2
* @brief Vector2クラス
*/
class Vector2 {
public:
    //! x
    float x;
    //! y
    float y;
public:
    static const Math::Vector2 ZERO;
    static const Math::Vector2 LEFT;
    static const Math::Vector2 RIGHT;
    static const Math::Vector2 UP;
    static const Math::Vector2 DOWN;
public:
    /**
    * @brief コンストラクタ
    */
    Vector2(float x = 0.0f, float y = 0.0f);
    /**
    * @brief コピーコンストラクタ
    */
    Vector2(const Vector2& v);

    /**
    * @brief 代入演算子
    */
    Vector2& operator=(const Vector2& v);

    /**
    * @brief 等値演算子
    */
    bool operator==(const Vector2& v)const;
    /**
    * @brief 等値演算子
    */
    bool operator !=(const Vector2& v) const;
    /**
    * @brief 0ベクトルの取得
    */
    static Vector2 zero();
    /**
    * @brief 単項プラス演算子
    */
    Vector2 operator +() const;
    /**
    * @brief 単項マイナス演算子
    */
    Vector2 operator -() const;
    /**
    * @brief 加算
    */
    Vector2 operator +(const Vector2& v) const;
    /**
    * @brief 減算
    */
    Vector2 operator -(const Vector2& v) const;
    /**
    * @brief スカラー倍
    */
    Vector2 operator *(float s) const;
    /**
    * @brief スカラー倍
    */
    friend Vector2 operator *(float s, const Vector2& v);
    /**
    * @brief スカラー除算
    */
    Vector2 operator /(float s) const;
    /**
    * @brief スカラー除算
    */
    friend Vector2 operator /(float s, const Vector2& v);
    /**
    * @brief 加算代入演算子
    */
    Vector2& operator +=(const Vector2& v);
    /**
    * @brief 減算代入演算子
    */
    Vector2& operator -=(const Vector2& v);
    /**
    * @brief 乗算代入演算子
    */
    Vector2& operator *=(float s);
    /**
    * @brief 除算代入演算子
    */
    Vector2& operator /=(float s);
    /**
    * @brief 大きさの2乗を返す
    * @return ベクトルの大きさの2乗
    */
    float lengthSq() const;
    /**
    * @brief 大きさを返す
    * @return ベクトルの大きさ
    */
    float length() const;
    /**
    * @brief ベクトルを正規化する
    */
    void normalize();
    /**
    * @brief 正規化されたベクトルを取得
    */
    Vector2 getNormal() const;
    /**
    * @brief 内積
    * @param v 計算するベクトル
    * @return 内積
    */
    float dot(const Vector2& v) const;
    /**
    * @brief 外積
    * @param v 計算するベクトル
    * @return 外積
    */
    float cross(const Vector2& v) const;
    /**
    * @brief ベクトルのクランプ処理
    * @param min 下限
    * @param max 上限
    */
    void clamp(const Vector2& min, const Vector2& max);

    /**
    * @brief Vector3に変換する
    */
    Vector3 toVector3() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
};

/**
* @brief 内積
* @param A ベクトル1
* @param B ベクトル2
* @return A・B
*/
inline float dot(const Vector2& A, const Vector2& B) {
    return A.dot(B);
}

/**
* @brief 外積
* @param A ベクトル1
* @param B ベクトル2
* @return A×B
*/
inline float cross(const Vector2& A, const Vector2& B) {
    return A.cross(B);
}

/**
* @brief ベクトルの補間
* @param v1 始点
* @param v2 終点
* @param t 補間係数
* @return 補間後のベクトル
*/
inline Vector2 lerp(const Vector2& v1, const Vector2& v2, float t) {
    t = MathUtility::clamp<float>(t, 0, 1);
    return v1 * (1 - t) + v2 * t;
}

/**
* @brief 反射ベクトルを求める
* @param vector 現在のベクトル
* @param normal 法線ベクトル
* @return 反射後のベクトル
*/
inline Vector2 reflect(const Vector2& vector, const Vector2& normal) {
    float L = (-normal).dot(vector);
    return Vector2(vector + normal * 2 * L);
}

} //Math
} //Framework 