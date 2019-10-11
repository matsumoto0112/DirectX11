#pragma once
#include <memory>
#include "Framework/Graphics/Renderer/AlphaBlend.h"
#include "Framework/Graphics/Renderer/RasterizerState.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Pipeline
* @brief �`��p�C�v���C���Ǘ��N���X
*/
class Pipeline {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Pipeline(std::shared_ptr<AlphaBlend> alphaBlend,
        std::shared_ptr<RasterizerState> rasterizer);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Pipeline();
    /**
    * @brief �R���e�L�X�g�̏�Ԃ��N���A����
    */
    virtual void clearState();
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