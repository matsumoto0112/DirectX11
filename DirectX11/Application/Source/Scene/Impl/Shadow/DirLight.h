#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class PerspectiveCamera;
class OrthographicCamera;
} //Graphics 
} //Framework 

/**
* @class DirLight
* @brief �f�B���N�V���i�����C�g�e�X�g�V�[��
*/
class DirLight : public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    DirLight();
    /**
    * @brief �f�X�g���N�^
    */
    ~DirLight();
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
    virtual void unload() override;
    /**
    * @brief ���̃V�[��
    */
    virtual Framework::Define::SceneType next() override;
private:
    std::shared_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< �J����
    std::shared_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< �J����
};