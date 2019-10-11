#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class PerspectiveCamera;
} //Graphics 
} //Framework 

/**
* @class RenderModel
* @brief ���f���`��e�X�g�V�[��
*/
class RenderModel : public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    RenderModel();
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderModel();
    /**
    * @brief �V�[���ǂݍ��ݏ���
    */
    virtual void load(Framework::Scene::Collecter& collecter) override;
    /**
    * @brief �X�V
    */
    virtual void update() override;
    /**
    * @brief �V�[���I�������𖞂����Ă��邩
    */
    virtual bool isEndScene() const override;
    /**
    * @brief �`��
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
    /**
    * @brief �I������
    */
    virtual void end() override;
    /**
    * @brief ���̃V�[��
    */
    virtual Framework::Define::SceneType next() override;
private:
    std::shared_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< �J����
};