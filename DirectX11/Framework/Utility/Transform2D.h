#pragma once
#include "Math/Vector2.h"

namespace Framework {

namespace Math {
class Matrix4x4;
} //Math 

namespace Utility {

/**
* @class Transform2D
* @brief 2Dトランスフォーム
*/
class Transform2D
{
public:
    /**
    * @brief コンストラクタ
    * @param position 座標
    * @param scale 大きさ
    * @param rotate 回転
    */
    Transform2D(const Math::Vector2& position, const Math::Vector2& scale, float rotate);
    /**
    * @brief デストラクタ
    */
    ~Transform2D();
    /**
    * @brief 座標の設定
    */
    void setPosition(const Math::Vector2& position);
    /**
    * @brief 座標の取得
    */
    const Math::Vector2& getPosition() const;
    /**
    * @brief 大きさの設定
    */
    void setScale(const Math::Vector2& scale);
    /**
    * @brief 大きさの取得
    */
    const Math::Vector2& getScale() const;
    /**
    * @brief 回転の設定
    */
    void setRotate(float rotate);
    /**
    * @brief 回転の取得
    */
    float getRotate() const;
    /**
    * @brief 座標変換行列の作成
    */
    Math::Matrix4x4 createSRTMatrix() const;
    /**
    * @brief ローカル座標変換行列の作成
    */
    Math::Matrix4x4 createLocalSRTMatrix() const;
    /**
    * @brief ペアレントの設定
    */
    void setParent(Transform2D* parent);
    /**
    * @brief ペアレントの取得
    */
    const Transform2D* getParent() const;
private:
    Math::Vector2 mPosition; //!< 座標
    Math::Vector2 mScale; //!< 大きさ
    float mRotate; //!< 回転
    Transform2D* mParent; //!< 親のTransform
};
} //Utility 
} //Framework 
