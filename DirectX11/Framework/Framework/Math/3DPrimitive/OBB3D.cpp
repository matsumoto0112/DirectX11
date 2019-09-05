#include "OBB3D.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Utility/Debug.h"

namespace {
//投影線分長を取得
float lengthSegmentOnSearateAxis(
    const Framework::Math::Vector3& sep,
    const Framework::Math::Vector3& e1,
    const Framework::Math::Vector3& e2,
    const Framework::Math::Vector3& e3 = Framework::Math::Vector3::ZERO) {
    float r1 = Framework::Math::MathUtility::abs(sep.dot(e1));
    float r2 = Framework::Math::MathUtility::abs(sep.dot(e2));
    float r3 = e3 != Framework::Math::Vector3::ZERO ? Framework::Math::MathUtility::abs(sep.dot(e3)) : 0;
    return r1 + r2 + r3;
}
}
namespace Framework {
namespace Math {

bool OBB3D::isCollide(const OBB3D& other) const {
    //各方向ベクトル
    //自分のをまず計算する
    Vector3 nae1 = mNormalDirect[0], ae1 = nae1 * mLength.x;
    Vector3 nae2 = mNormalDirect[1], ae2 = nae2 * mLength.y;
    Vector3 nae3 = mNormalDirect[2], ae3 = nae3 * mLength.z;

    //相手のを計算する
    Vector3 nbe1 = other.mNormalDirect[0], be1 = nbe1 * other.mLength.x;
    Vector3 nbe2 = other.mNormalDirect[1], be2 = nbe2 * other.mLength.y;
    Vector3 nbe3 = other.mNormalDirect[2], be3 = nbe3 * other.mLength.z;

    //中心との距離
    Vector3 interval = mPosition - other.mPosition;

    //分離軸：ae1
    float ra = ae1.length();
    float rb = lengthSegmentOnSearateAxis(nae1, be1, be2, be3);
    float L = MathUtility::abs(interval.dot(nae1));
    if (L > ra + rb)return false;

    //分離軸：ae2
    ra = ae2.length();
    rb = lengthSegmentOnSearateAxis(nae2, be1, be2, be3);
    L = MathUtility::abs(interval.dot(nae2));
    if (L > ra + rb)return false;

    //分離軸：ae3
    ra = ae3.length();
    rb = lengthSegmentOnSearateAxis(nae3, be1, be2, be3);
    L = MathUtility::abs(interval.dot(nae3));
    if (L > ra + rb)return false;

    //分離軸：be1
    ra = lengthSegmentOnSearateAxis(nbe1, ae1, ae2, ae3);
    rb = be1.length();
    L = MathUtility::abs(interval.dot(nbe1));
    if (L > ra + rb)return false;

    //分離軸：be2
    ra = lengthSegmentOnSearateAxis(nbe2, ae1, ae2, ae3);
    rb = be2.length();
    L = MathUtility::abs(interval.dot(nbe2));
    if (L > ra + rb)return false;

    //分離軸：be3
    ra = lengthSegmentOnSearateAxis(nbe3, ae1, ae2, ae3);
    rb = be3.length();
    L = MathUtility::abs(interval.dot(nbe3));
    if (L > ra + rb)return false;

    //分離軸：c11
    Vector3 cross = nae1.cross(nbe1);
    ra = lengthSegmentOnSearateAxis(cross, ae2, ae3);
    rb = lengthSegmentOnSearateAxis(cross, be2, be3);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離軸：c12
    cross = nae1.cross(nbe2);
    ra = lengthSegmentOnSearateAxis(cross, ae2, ae3);
    rb = lengthSegmentOnSearateAxis(cross, be1, be3);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離軸：c13
    cross = nae1.cross(nbe3);
    ra = lengthSegmentOnSearateAxis(cross, ae2, ae3);
    rb = lengthSegmentOnSearateAxis(cross, be1, be2);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離軸：c21
    cross = nae2.cross(nbe1);
    ra = lengthSegmentOnSearateAxis(cross, ae1, ae3);
    rb = lengthSegmentOnSearateAxis(cross, be2, be3);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離軸：c22
    cross = nae2.cross(nbe2);
    ra = lengthSegmentOnSearateAxis(cross, ae1, ae3);
    rb = lengthSegmentOnSearateAxis(cross, be1, be3);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離軸：c23
    cross = nae2.cross(nbe3);
    ra = lengthSegmentOnSearateAxis(cross, ae1, ae2);
    rb = lengthSegmentOnSearateAxis(cross, be1, be2);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離軸：c31
    cross = nae3.cross(nbe1);
    ra = lengthSegmentOnSearateAxis(cross, ae1, ae2);
    rb = lengthSegmentOnSearateAxis(cross, be2, be3);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離軸：c32
    cross = nae3.cross(nbe2);
    ra = lengthSegmentOnSearateAxis(cross, ae1, ae2);
    rb = lengthSegmentOnSearateAxis(cross, be1, be3);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離軸：c33
    cross = nae3.cross(nbe3);
    ra = lengthSegmentOnSearateAxis(cross, ae1, ae2);
    rb = lengthSegmentOnSearateAxis(cross, be1, be2);
    L = MathUtility::abs(interval.dot(cross));
    if (L > ra + rb)return false;

    //分離平面が存在しないので衝突している
    return true;
}

float OBB3D::getLength(int elem) const {
    switch (elem) {
    case 0:
        return mLength.x;
    case 1:
        return mLength.y;
    case 2:
        return mLength.z;
    default:
        MY_ASSERTION(false, "elemが範囲外です");
        return 0;
    }
}

void OBB3D::setPosition(const Math::Vector3& position) {
    this->mPosition = position;
}

void OBB3D::setNormal(int axis, const Math::Vector3& normal) {
    MY_ASSERTION(0 <= axis && axis < 3, "軸が不正な値です");
    mNormalDirect[axis] = normal;
}

void OBB3D::setLength(const Math::Vector3& length) {
    mLength = length;
}

} //Math 
} //Framework 