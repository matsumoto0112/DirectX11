#pragma once
#include <memory>
#include "Framework/Graphics/Renderer/AlphaBlend.h"
#include "Framework/Graphics/Renderer/RasterizerState.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class RenderState
* @brief �`��p�C�v���C���Ǘ��N���X
*/
class RenderState {
public:
    /**
    * @brief �R���X�g���N�^
    */
    RenderState(std::shared_ptr<AlphaBlend> alphaBlend,
        std::shared_ptr<RasterizerState> rasterizer);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~RenderState();
    /**
    * @brief �`��p�C�v���C�����Z�b�g����
    */
    virtual void setPipeline();
private:
    PROPERTY_POINTER(std::shared_ptr<AlphaBlend>, mAlphaBlend, AlphaBlend);
    PROPERTY_POINTER(std::shared_ptr<RasterizerState>, mRasterizer, RasterizerState);
};

} //Graphics 
} //Framework 