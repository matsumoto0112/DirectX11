#pragma once
#include <memory>
#include "Source/GameObject/GameObject3D.h"
#include "Source/GameObject/Collider.h"

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
    * @param collider コライダー
    */
    Collidable3DObject(const Framework::Utility::Transform& transform,
        IMainSceneMediator& mediator,
        Define::ModelType modelType,
        std::unique_ptr<Collider> collider);
    /**
    * @brief デストラクタ
    */
    virtual ~Collidable3DObject();
    /**
    * @brief 描画
    */
    virtual void draw() override;
    /**
    * @brief コライダーポインタを取得する
    */
    Collider* getColliderPtr() const { return mCollider.get(); }
protected:
    /**
    * @brief コライダーを作成する
    */
    virtual std::unique_ptr<Collider> createCollider() = 0;
protected:
    std::unique_ptr<Collider> mCollider; //!< コライダー
};