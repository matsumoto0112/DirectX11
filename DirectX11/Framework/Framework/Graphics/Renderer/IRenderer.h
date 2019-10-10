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
* @brief �`��C���^�[�t�F�[�X
*/
class IRenderer {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IRenderer() = default;
    /**
    * @brief �`��J�n
    */
    virtual void begin() = 0;
    /**
    * @brief �`��I��
    */
    virtual void end() = 0;
    /**
    * @brief �X�v���C�g��`�悷��
    * @param sprite �`�悷��X�v���C�g
    */
    virtual void render(std::shared_ptr<Sprite2D> sprite) = 0;
    /**
    * @brief �X�v���C�g��`�悷��
    * @param sprite �`�悷��X�v���C�g
    */
    virtual void render(std::shared_ptr<Sprite3D> sprite) = 0;
    /**
    * @brief ���f����`�悷��
    * @param model �`�悷�郂�f��
    * @param transform �`�悷�郂�f���̃g�����X�t�H�[��
    */
    virtual void render(std::shared_ptr<Model> model, const Utility::Transform& transform) = 0;
};

} //Graphics 
} //Framework 