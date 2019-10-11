#pragma once
#include <memory>
#include "Framework/Graphics/Renderer/AlphaBlend.h"
#include "Framework/Graphics/Renderer/RenderTargetView.h"
#include "Framework/Graphics/Renderer/Viewport.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class IDrawable;

/**
* @class Pipeline
* @brief �`��p�C�v���C���Ǘ��N���X
*/
class Pipeline {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Pipeline(std::shared_ptr<RenderTargetView> renderTarget,
        std::shared_ptr<AlphaBlend> alphaBlend,
        const Viewport& viewport);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Pipeline();
    /**
    * @brief �`��J�n
    */
    virtual void begin();
    /**
    * @brief �`��I��
    */
    virtual void end();
    /**
    * @brief �`�悷��
    * @param drawable �`��Ώ�
    */
    virtual void render(IDrawable* drawable);
private:
    PROPERTY_POINTER(std::shared_ptr<RenderTargetView>, mRenderTarget, RenderTargetView);
    PROPERTY_POINTER(std::shared_ptr<AlphaBlend>, mAlphaBlend, AlphaBlend);
    PROPERTY(Viewport, mViewport, Viewport);
};

} //Graphics 
} //Framework 