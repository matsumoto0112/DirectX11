#pragma once
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {
class PerspectiveCamera;
class OrthographicCamera;

/**
* @class IRenderer
* @brief 描画インターフェース
*/
class IRenderer {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IRenderer() = default;
    /**
    * @brief 描画開始
    */
    virtual void begin() = 0;
    /**
    * @brief 描画終了
    */
    virtual void end() = 0;
    /**
    * @brief スプライトを描画する
    * @param sprite 描画するスプライト
    */
    virtual void render(std::shared_ptr<Sprite2D> sprite) = 0;
    /**
    * @brief スプライトを描画する
    * @param sprite 描画するスプライト
    */
    virtual void render(std::shared_ptr<Sprite3D> sprite) = 0;
    /**
    * @brief モデルを描画する
    * @param model 描画するモデル
    * @param transform 描画するモデルのトランスフォーム
    */
    virtual void render(std::shared_ptr<Model> model, const Utility::Transform& transform) = 0;
    /**
    * @brief 描画したターゲットのテクスチャを取得する
    */
    virtual std::shared_ptr<Texture> getRenderedTexture() const = 0;
protected:
    PROPERTY(Color4, mBackColor, BackColor);
    PROPERTY_POINTER(PerspectiveCamera*, mCurrentPerspectiveCamera, CurrentPerspectiveCamera);
    PROPERTY_POINTER(OrthographicCamera*, mCurrentOrthographicCamera, CurrentOrthographicCamera);
};

} //Graphics 
} //Framework 