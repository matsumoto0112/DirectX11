#pragma once
#include <memory>
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Utility/Transform.h"
#include "Framework/Utility/Property.h"
#include "Source/GameObject/IMainSceneMediator.h"

/**
* @class GameObject
* @brief ゲームオブジェクト基底クラス
*/
class GameObject {
public:
    /**
    * @brief コンストラクタ
    */
    GameObject(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator)
        :mMediator(mediator), mTransform(transform) {};
    /**
    * @brief デストラクタ
    */
    virtual ~GameObject() = default;
    /**
    * @brief 初期化処理
    */
    virtual void initialize() {};
    /**
    * @brief 更新
    */
    virtual void update() {};
    /**
    * @brief 描画する
    * @param renderer 使用する描画インターフェース
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) {};
    /**
    * @brief トランスフォームのポインタを取得する
    */
    Framework::Utility::Transform* getTransformPtr() { return &mTransform; }
protected:
    IMainSceneMediator& mMediator; //!< メインシーン仲介者
protected:
    PROPERTY(Framework::Utility::Transform, mTransform, Transform);
};