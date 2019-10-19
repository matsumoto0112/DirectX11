#pragma once
#include "Framework/Scene/SceneBase.h"

/**
* @class TestScene
* @brief discription
*/
class TestScene :public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    TestScene();
    /**
    * @brief �f�X�g���N�^
    */
    ~TestScene();


    // SceneBase ����Čp������܂���
    virtual void load(Framework::Scene::Collecter& collecter) override;

    virtual void update() override;

    virtual bool isEndScene() const override;

    virtual void draw(Framework::Graphics::IRenderer * renderer) override;

    virtual void unload() override;

    virtual Framework::Define::SceneType next() override;
private:

};