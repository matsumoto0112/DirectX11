#pragma once
#include "Framework/Utility/Property.h"
#include "Framework/Graphics/Shader/Effect.h"

namespace Framework {
namespace Graphics {

/**
* @class IDrawable
* @brief 描画可能オブジェクト
*/
class IDrawable {
public:
    IDrawable(std::shared_ptr<Effect> effect)
        :mEffect(effect) { };
    /**
    * @brief デストラクタ
    */
    virtual ~IDrawable() = default;
    /**
    * @brief 描画処理
    */
    virtual void draw() = 0;
protected:
    PROPERTY_POINTER(std::shared_ptr<Effect>, mEffect, Effect);
};

} //Graphics 
} //Framework 