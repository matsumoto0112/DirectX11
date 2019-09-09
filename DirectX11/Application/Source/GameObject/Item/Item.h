#pragma once
#include "Source/GameObject/Collidable3DObject.h"

/**
* @class Item
* @brief アイテム基底クラス
*/
class Item :public Collidable3DObject {
public:
    /**
    * @brief コンストラクタ
    */
    Item(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    ~Item();
    /**
    * @brief 更新
    */
    virtual void update() override;
    /**
    * @brief ディスパッチ関数
    */
    virtual void dispatch(Collidable3DObject* other) override;
    /**
    * @brief プレイヤーとの衝突時処理
    */
    virtual void hit(Player* other) override;
    /**
    * @brief コライダーを作成する
    */
    virtual std::unique_ptr<Collider> createCollider() override;
private:
};