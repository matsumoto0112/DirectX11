#pragma once

#include "Source/GameObject/Collidable3DObject.h"

/**
* @class Enemy
* @brief 敵クラス
*/
class Enemy : public Collidable3DObject {
public:
    /**
    * @brief コンストラクタ
    */
    Enemy(const Framework::Utility::Transform& transform,
        const Framework::Graphics::Color4& enemyColor,
        IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~Enemy();
    /**
    * @brief 初期化処理
    */
    virtual void initialize() override;
    /**
    * @brief ディスパッチ関数
    */
    virtual void dispatch(Collidable3DObject* other) override;

    virtual void hit(Player* other) override;
    /**
    * @brief 弾との衝突時処理
    */
    virtual void hit(Bullet* other) override;
    /**
    * @brief 描画
    */
    virtual void draw() override;
protected:
    /**
    * @brief 自身のコライダーを作成する
    */
    virtual std::unique_ptr<Collider> createCollider() override;
protected:
    Framework::Graphics::Color4 mColor; //!< 色
};