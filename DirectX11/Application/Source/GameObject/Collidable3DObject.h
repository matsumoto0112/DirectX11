#pragma once
#include <memory>
#include "Source/GameObject/GameObject3D.h"
#include "Source/GameObject/Collider.h"

class Player;
class Bullet;
class Enemy;

/**
* @class Collidable3DObject
* @brief 衝突可能な3Dオブジェクト
*/
class Collidable3DObject : public GameObject3D {
public:
    /**
    * @brief コンストラクタ
    * @param transform トランスフォーム
    * @param mediator メインシーン仲介者
    * @param modelType モデルの種類
    */
    Collidable3DObject(const Framework::Utility::Transform& transform,
        IMainSceneMediator& mediator,
        Define::ModelType modelType);
    /**
    * @brief デストラクタ
    */
    virtual ~Collidable3DObject();
    /**
    * @brief 初期化
    */
    virtual void initialize() override;
    /**
    * @brief 描画
    */
    virtual void draw() override;
    /**
    * @brief コライダーポインタを取得する
    */
    Collider* getColliderPtr() const { return mCollider.get(); }

    virtual void dispatch(Collidable3DObject* other) = 0;
    virtual void hit(Player* other) {};
    virtual void hit(Bullet* other) {};
    virtual void hit(Enemy* other) {};
protected:
    /**
    * @brief コライダーを作成する
    */
    virtual std::unique_ptr<Collider> createCollider() = 0;
protected:
    PROPERTY(bool, mIsAlive, IsAlive);
protected:
    std::unique_ptr<Collider> mCollider; //!< コライダー
};