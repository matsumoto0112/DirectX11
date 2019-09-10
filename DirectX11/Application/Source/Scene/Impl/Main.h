#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"
#include "Source/GameObject/IMainSceneMediator.h"

namespace Framework {
namespace Graphics {
class AlphaBlend;
class Model;
class PerspectiveCamera;
} //Graphics 
} //Framework 

class GameObjectManager;
class FollowCamera;

/**
* @class Main
* @brief ���C���V�[�������N���X
*/
class Main : public Framework::Scene::SceneBase, public IMainSceneMediator {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Main();
    /**
    * @brief �f�X�g���N�^
    */
    ~Main();
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
    virtual Define::SceneType next() override;
    /**
    * @brief ���C���J�������擾����
    */
    virtual FollowCamera* getMainCamera() override;
    /**
    * @brief �v���C���[�|�C���^���擾����
    */
    virtual Player * getPlayer() override;
    /**
    * @brief �e�𔭎˂���
    */
    virtual void shotBullet(const Framework::Utility::Transform& transform) override;
    /**
    * @brief �f�o�b�OUI��ǉ�����
    */
    virtual void addDebugUI(std::shared_ptr<Framework::ImGUI::Window> window) override;
private:
    std::unique_ptr<GameObjectManager> mManager;
    std::unique_ptr<FollowCamera> mCamera;
    std::unique_ptr<Framework::Graphics::AlphaBlend> mAlphaBlend;
private:
    std::vector<std::shared_ptr<Framework::ImGUI::Window>> mDebugUIs;
};