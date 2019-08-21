#pragma once
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class TextureString;
} //Graphics 
} //Framework 

/**
* @class Title
* @brief discription
*/
class Title : public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Title();
    /**
    * @brief �f�X�g���N�^
    */
    ~Title();
    /**
    * @brief �V�[���f�[�^�̓ǂݍ���
    */
    virtual void load(Framework::Scene::Collecter& collecter) override;
    /**
    * @brief �X�V
    */
    virtual void update(float delta) override;
    /**
    * @brief �I�����Ă��邩
    */
    virtual bool isEndScene() const override;
    /**
    * @brief �`��
    */
    virtual void draw() override;
    /**
    * @brief �I������
    */
    virtual void end() override;
    /**
    * @brief ���̃V�[��
    */
    virtual Define::SceneType next() override;
private:
    std::unique_ptr<Framework::Graphics::TextureString> mTitleStr;
};
