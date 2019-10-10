#pragma once
#include <memory>
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Render/RenderTargetView.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Pipeline
* @brief discription
*/
class Pipeline {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Pipeline(std::shared_ptr<RenderTargetView> renderTarget,
        std::shared_ptr<AlphaBlend> alphaBlend);
    /**
    * @brief �f�X�g���N�^
    */
    ~Pipeline();

    void begin();
    void end();
private:
    PROPERTY_POINTER(std::shared_ptr<RenderTargetView>, mRenderTarget, RenderTargetView);
    PROPERTY_POINTER(std::shared_ptr<AlphaBlend>, mAlphaBlend, AlphaBlend);
};

} //Graphics 
} //Framework 