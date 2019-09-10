#pragma once
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Shader/Effect.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {
class Model;
/**
* @class ZTexCreater
* @brief Z�l���o�͂����e�N�X�`�����쐬����
*/
class ZTexCreater {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ZTexCreater(UINT width, UINT height, std::shared_ptr<Effect> effect);
    /**
    * @brief �f�X�g���N�^
    */
    ~ZTexCreater();
    /**
    * @brief �r���[�s���ݒ肷��
    */
    void setViewMatrix(const Math::Matrix4x4& view);
    /**
    * @brief �v���W�F�N�V�����s���ݒ肷��
    */
    void setProjectionMatrix(const Math::Matrix4x4& proj);
    /**
    * @brief �o�͊J�n
    */
    void begin();
    /**
    * @brief �o�͏I��
    */
    void end();

    void draw(Model* model);
private:
    std::shared_ptr<Effect> mEffect;
    std::shared_ptr<Texture> mTexture;
    std::unique_ptr<RenderTarget> mRenderTarget;
};

} //Graphics 
} //Framework 