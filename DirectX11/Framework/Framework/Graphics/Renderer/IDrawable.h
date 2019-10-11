#pragma once
#include "Framework/Utility/Property.h"
#include "Framework/Graphics/Shader/Effect.h"

namespace Framework {
namespace Graphics {

/**
* @class IDrawable
* @brief �`��\�I�u�W�F�N�g
*/
class IDrawable {
public:
    IDrawable(std::shared_ptr<Effect> effect)
        :mEffect(effect) { };
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IDrawable() = default;
    /**
    * @brief �`�揈��
    */
    virtual void draw() = 0;
protected:
    PROPERTY_POINTER(std::shared_ptr<Effect>, mEffect, Effect);
};

} //Graphics 
} //Framework 