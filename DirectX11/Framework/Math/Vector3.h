#pragma once

#include <ostream>
#include "Math/MathUtility.h"

namespace Framework {
namespace Math {

/**
* @class Vector3
* @brief Vector3クラス
*/
class Vector3 {
public:
    float x; //!< x
    float y; //!< y
    float z; //!< z
public:
    static const Vector3 ZERO;
    static const Vector3 LEFT;
    static const Vector3 RIGHT;
    static const Vector3 UP;
    static const Vector3 DOWN;
    static const Vector3 FORWORD;
    static const Vector3 BACK;
public:
    /**
    * @brief コンストラクタ
    */
    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    /**
    * @brief コピーコンストラクタ
    */
    Vector3(const Vector3& v);
    /**
    * @brief 代入演算子
    */
    Vector3& operator =(const Vector3& a);

    /**
    * @brief 等値演算子
    */
    bool operator ==(const Vector3 &a) const;
    /**
    * @brief 等値演算子
    */
    bool operator !=(const Vector3 &a) const;
    /**
    * @brief 0ベクトルの取得
    */
    static Vector3 zero();
    /**
    * @brief 単項プラス演算子
    */
    Vector3 operator +() const;
    /**
    * @brief 単項マイナス演算子
    */
    Vector3 operator -() const;
    /**
    * @brief 加算
    */
    Vector3 operator +(const Vector3 &a) const;
    /**
    * @brief 減算
    */
    Vector3 operator -(const Vector3 &a) const;
    /**
    * @brief スカラー倍
    */
    Vector3 operator *(float a) const;
    /**
    * @brief スカラー除算
    */
    Vector3 operator /(float a) const;
    /**
    * @brief スカラー倍
    */
    friend Vector3 operator *(float a, const Vector3& v);
    /**
    * @brief スカラー除算
    */
    friend Vector3 operator /(float a, const Vector3& v);
    /**
    * @brief 加算代入演算子
    */
    Vector3 &operator +=(const Vector3 &a);
    /**
    * @brief 減算代入演算子
    */
    Vector3 &operator -=(const Vector3 &a);
    /**
    * @brief 乗算代入演算子
    */
    Vector3 &operator *=(float a);
    /**
    * @brief 除算代入演算子
    */
    Vector3 &operator /=(float a);

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
    * @brief ベクトルの正規化
    * @return 正規化されたベクトルを返す
    */
    Vector3 getNormal() const;
    /**
    * @brief 内積
    * @param a 計算するベクトル
    * @return 内積
    */
    float dot(const Vector3 &a) const;
    /**
    * @brief 外積
    * @param a 計算するベクトル
    * @return 外積
    */
    Vector3 cross(const Vector3 &a) const;
    /**
    * @brief ベクトルのクランプ処理
    * @param min 下限
    * @param max 上限
    */
    void clamp(const Vector3& min, const Vector3& max);

    /**
    * @brief 内積
    * @param a aベクトル
    * @param b bベクトル
    */
    static float dot(const Vector3 &a, const Vector3 &b);
    /**
    * @brief 外積
    * @param a aベクトル
    * @param b bベクトル
    */
    static Vector3 cross(const Vector3 &a, const Vector3 &b);

    /**
    * @brief ストリーム演算子
    */
    friend std::ostream& operator<<(std::ostream& os, const Math::Vector3& v);

};

} //Math
} //Framework 