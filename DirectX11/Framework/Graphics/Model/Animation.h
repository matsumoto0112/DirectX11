#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {

class Motion;

/**
* @class Animation
* @brief �A�j���[�V�����Ǘ��N���X
*/
class Animation {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Animation();
    /**
    * @brief �f�X�g���N�^
    */
    ~Animation();
    /**
    * @brief ���[�V�����̒ǉ�
    * @param id ���[�V����ID
    * @param motion �ǉ����郂�[�V����
    */
    void addMotion(int id, std::unique_ptr<Motion> motion);
    /**
    * @brief ���[�V�����̍X�V
    * @param delta ��������
    */
    void update(float delta);
    /**
    * @brief �Đ��A�j���[�V�����̕ύX
    * @param id �ύX����A�j���[�V����ID
    */
    void changeAnimation(int id);
    /**
    * @brief ���݂̃��[�V�����̍s����擾
    */
    Math::Matrix4x4 getAnimationMatrix(int bone);
private:
    float mTime; //!< �A�j���[�V�����Đ�����
    int mCurrentMotion; //!< �Đ����̃A�j���[�V����ID
    std::unordered_map<int, std::unique_ptr<Motion>> mMotions; //!< ���[�V�������X�g
};

} //Graphics
} //Framework 
