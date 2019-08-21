#pragma once

#include <memory>
#include "Framework/Define/SceneType.h"

namespace Framework {
namespace Scene {
class Collecter;

/**
* @class SceneBase
* @brief �V�[���C���^�[�t�F�[�X
*/
class SceneBase {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~SceneBase() = default;
    /**
    * @brief �V�[���̃f�[�^�ǂݍ���
    * @param collecter �V�[���f�[�^�R���N�^
    */
    virtual void load(Collecter& collecter) = 0;
    /**
    * @brief �X�V
    * @param delta �O�t���[������̍�������
    */
    virtual void update(float delta) = 0;
    /**
    * @brief �V�[�����I�����Ă��邩
    */
    virtual bool isEndScene() const = 0;
    /**
    * v�`��
    */
    virtual void draw() = 0;
    /**
    * @brief �V�[���̏I������
    */
    virtual void end() = 0;
    /**
    * @brief ���̃V�[��
    */
    virtual Define::SceneType next() = 0;
};

} //Scene 
} //Framework 
