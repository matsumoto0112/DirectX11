#pragma once
#include "Framework/Define/Resource/Model.h"
#include "Framework/Graphics/Model/Model.h"
#include "Source/GameObject/GameObject.h"

/**
* @class GameObject3D
* @brief 3Dゲームオブジェクト基底クラス
*/
class GameObject3D :public GameObject {
public:
    /**
    * @brief コンストラクタ
    * @param transform 初期状態のトランスフォーム
    * @param modelType モデルの種類
    */
    GameObject3D(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator, Define::ModelType modelType);
    /**
    * @brief デストラクタ
    */
    virtual ~GameObject3D();
    /**
    * @brief 描画する
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
protected:
    std::shared_ptr<Framework::Graphics::Model> mModel; //!< モデルデータ
};