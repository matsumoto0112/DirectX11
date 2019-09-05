#pragma once
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Math {

/**
* @class AABB3D
* @brief 3DAABB
*/
class AABB3D {
private:
    Vector3 mMin;
    Vector3 mMax;
public:
    Property<Vector3> min{ mMin };
    Property<Vector3> max{ mMax };
public:
    /**
    * @brief デフォルトコンストラクタ
    */
    AABB3D();
    /**
    * @brief コンストラクタ
    */
    AABB3D(const Vector3& min, const Vector3& max);
    /**
    * @brief デストラクタ
    */
    ~AABB3D();
    /**
    * @brief 大きさを取得する
    */
    Vector3 size() const { return mMax - mMin; }
    /**
    * @brief Xの大きさを取得する
    */
    float xSize() const { return mMax.x - mMin.x; }
    /**
    * @brief Yの大きさを取得する
    */
    float ySize() const { return mMax.y - mMin.y; }
    /**
    * @brief Zの大きさを取得する
    */
    float zSize() const { return mMax.z - mMin.z; }
    /**
    * @brief 中心座標を取得する
    */
    Vector3 center() const { return (mMax + mMin) * 0.5f; }
    /**
    * @brief ボックスに点を追加する
    */
    void add(const Vector3& p);
    /**
    * @brief boxを座標変換した後のAABBを構築する
    */
    void setToTransformedAABB(const AABB3D& box, const Matrix4x4& m);
    /**
    * @brief 点を含んでいるか
    */
    bool contains(const Vector3& p) const;
    /**
    * @brief 二つのAABBが重なっているか
    */
    static bool intersect(const AABB3D& box1, const AABB3D& box2);
};

} //Math 
} //Framework 