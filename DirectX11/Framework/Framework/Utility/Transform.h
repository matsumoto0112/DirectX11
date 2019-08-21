#pragma once
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Quaternion.h"

namespace Framework {

namespace Math {
class Matrix4x4;
} //Math 

namespace Utility {

/**
* @class Transform
* @brief 3Dトランスフォームクラス
*/
class Transform {
public:
    /**
    * @brief デフォルトコンストラクタ
    */
    Transform();
    /**
    * @brief コンストラクタ
    * @param position 座標
    * @param rotate 回転
    * @param scale 大きさ
    */
    Transform(const Math::Vector3& position,
        const Math::Quaternion& rotate,
        const Math::Vector3& scale);
    /**
    * @brief デストラクタ
    */
    virtual ~Transform();
    /**
    * @brief 座標の取得
    */
    const Math::Vector3& getPosition() const { return mPosition; }
    Math::Vector3 getGlobalPostition() const;
    /**
    * @brief 回転の取得
    */
    const Math::Quaternion& getRotate() const { return mRotation; }
    Math::Quaternion getGlobalRotate() const;
    /**
    * @brief 大きさの取得
    */
    const Math::Vector3& getScale() const { return mScale; }
    Math::Vector3 getGlobalScale() const;
    /**
    * @brief 座標の設定
    */
    void setPosition(const Math::Vector3& position) { mPosition = position; }
    /**
    * @brief 回転の設定
    */
    void setRotate(const Math::Quaternion& rotate) { mRotation = rotate; }
    /**
    * @brief 大きさの設定
    */
    void setScale(const Math::Vector3& scale) { mScale = scale; }
    /**
    * @brief SRT行列の作成
    */
    Math::Matrix4x4 createSRTMatrix() const;
    /**
    * @brief ローカルのSRT行列の作成
    */
    Math::Matrix4x4 createLocalSRTMatrix() const;
    void setParent(Transform* parent);

private:
    Transform* mParent; //!< 親のトランスフォーム
    Math::Vector3 mPosition; //!< 座標
    Math::Quaternion mRotation; //!< 回転
    Math::Vector3 mScale; //!< 大きさ
};

} //Utility 
} //Framework 
