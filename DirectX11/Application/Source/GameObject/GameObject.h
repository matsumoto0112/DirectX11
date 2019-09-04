#pragma once
#include <memory>
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
    virtual void update() {};
    virtual void draw() {};

    ReadonlyProperty<Framework::Utility::Transform> transform{ mTransform };
protected:
    IMainSceneMediator& mMediator; //!< メインシーン仲介者
    Framework::Utility::Transform mTransform;
};