#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class RenderTarget;

/**
* @class BackBufferRenderer
* @brief �o�b�N�o�b�t�@�Ɍ����ĕ`�悷��f�o�C�X
*/
class BackBufferRenderer : public IRenderer {
public:
    /**
    * @brief �R���X�g���N�^
    */
    BackBufferRenderer(std::shared_ptr<Texture2D> backBufferTexture, UINT width, UINT height, const Color4& backColor);
    /**
    * @brief �f�X�g���N�^
    */
    ~BackBufferRenderer();
    /**
    * @brief �`��J�n
    */
    virtual void begin() override;
    /**
    * @brief �`��I��
    */
    virtual void end() override;
    /**
    * @brief �`�揈��
    */
    virtual void render(IDrawable* drawable) override;
};

} //Graphics 
} //Framework 