#pragma once

namespace Framework {
namespace Math {
class Vector3;
class Matrix4x4;
class Quaternion;

/**
* @class Matrix4x3
* @brief 4x3行列
*/
class Matrix4x3 {
public:
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    float tx, ty, tz;
public:
    /**
    * @brief 恒等行列を設定する
    */
    void identity();
    /**
    * @brief 平行移動成分を0にする
    */
    void zeroTranslation();
    /**
    * @brief 平行移動成分の設定
    */
    Matrix4x3& setTranslation(const Vector3& d);
    /**
    * @brief 平行移動成分を設定した行列のセットアップ
    */
    Matrix4x3& setupTranslation(const Vector3& d);

    /**
    * @brief X軸周りの回転のセットアップ
    * @param degree 回転量（度）
    */
    Matrix4x3& setupRotateX(float degree);
    /**
    * @brief Y軸周りの回転のセットアップ
    * @param degree 回転量（度）
    */
    Matrix4x3& setupRotateY(float degree);
    /**
    * @brief Z軸周りの回転のセットアップ
    * @param degree 回転量（度）
    */
    Matrix4x3& setupRotateZ(float degree);
    /**
    * @brief 任意軸周りの回転のセットアップ
    * @param axis 軸（単位ベクトル）
    * @param degree 回転量（度）
    */
    Matrix4x3& setupRotate(const Vector3& axis, float degree);

    Matrix4x3& setupRotate(const Quaternion& rotate);
    /**
    * @brief 各軸スケーリング行列のセットアップ
    */
    Matrix4x3& setupScale(const Vector3& s);

    friend Vector3 operator *(const Vector3& p, const Matrix4x3& m);
    friend Vector3& operator *=(Vector3& p, const Matrix4x3& m);

    /**
    * @brief 3x3部分の行列式
    */
    static float determinant(const Matrix4x3& m);

    /**
    * @brief 逆行列を計算する
    */
    static Matrix4x3 inverse(const Matrix4x3& m);
    /**
    * @brief 4x4行列に変換する
    */
    Matrix4x4 convertMatrix4x4() const;

    Matrix4x3 operator *(const Matrix4x3& a);
    Matrix4x3& operator *=(const Matrix4x3& a);
};

} //Math 
} //Framework 