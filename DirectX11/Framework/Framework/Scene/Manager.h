#pragma once

#include <memory>
#include <unordered_map>
#include "Framework/Define/SceneType.h"

namespace Framework {
namespace Graphics {
class IRenderer;
} //Graphics 
namespace Scene {
class SceneBase;
class Collecter;

/**
* @class Manager
* @brief �V�[���Ǘ��N���X
*/
class Manager {
private:
    using ScenePtr = std::unique_ptr<SceneBase>;
    using ScenePtrContainer = std::unordered_map<Define::SceneType, ScenePtr>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    Manager();
    /**
    * @brief �f�X�g���N�^
    */
    ~Manager();
    /**
    * @brief �X�V
    */
    void update();
    /**
    * @brief �`��
    */
    void draw(Graphics::IRenderer* renderer);
    /**
    * @brief �V�[���̓o�^
    * @param type �V�[���̎��
    * @param scene �V�[���f�[�^
    */
    void registerScene(Define::SceneType type, ScenePtr scene);
    /**
    * @brief �V�[����ǂݍ���
    */
    void loadScene(Define::SceneType next);
private:
    /**
    * @brief ���̃V�[���̎擾
    * @param next ���̃V�[���̎��
    */
    SceneBase* getNextScene(Define::SceneType next);
private:
    SceneBase* mCurrentScene; //!< ���݂̃V�[��
    ScenePtrContainer mCreatedScene; //!< ���ɍ��ꂽ�V�[�����X�g
    std::unique_ptr<Collecter> mCollecter; //!< �V�[���R���N�^
};

} //Scene 
} //Framework 
