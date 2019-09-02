#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"
#include "Source/GameObject/IMainSceneMediator.h"

namespace Framework {
namespace Graphics {
class Model;
class PerspectiveCamera;
} //Graphics 
} //Framework 

class GameObjectManager;

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
    virtual void load(Framework::Scene::Collecter& collecter) override;

    virtual void update() override;

    virtual bool isEndScene() const override;

    virtual void draw() override;

    virtual void end() override;

    virtual Define::SceneType next() override;

    virtual Framework::Graphics::PerspectiveCamera* getMainCamera() override;

    virtual void shotBullet(const Framework::Utility::Transform& transform) override;
private:
    std::unique_ptr<GameObjectManager> mManager;
    std::unique_ptr<Framework::Graphics::PerspectiveCamera> mCamera;
};