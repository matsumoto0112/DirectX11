#pragma once
#include "Source/GameObject/Enemy/Enemy.h"

/**
* @class NormalEnemy
* @brief �ʏ�G
*/
class NormalEnemy : public Enemy {
public:
    struct Parameter {
    public:
        Framework::Graphics::Color4 color;
        float moveSpeed;
    };
public:
    /**
    * @brief �R���X�g���N�^
    */
    NormalEnemy(const Framework::Utility::Transform& transform, const Parameter& parameter, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~NormalEnemy();
    /**
    * @brief �X�V����
    */
    virtual void update() override;
private:
    float mMoveSpeed;
};