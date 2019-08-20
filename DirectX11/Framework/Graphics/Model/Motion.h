#pragma once
#include <vector>
#include "Math/Matrix4x4.h"
namespace Framework {
namespace Graphics {

/**
* @class Motion
* @brief ���[�V�����Ǘ��N���X
*/
class Motion {
public:
    /**
    * @brief �R���X�g���N�^
    * @param keyFrame �L�[�t���[����
    */
    Motion(int keyFrame, int bone);
    /**
    * @brief �f�X�g���N�^
    */
    ~Motion();
    /**
    * @brief �L�[�t���[���P�ʂł̍s��̐ݒ�
    * @param frame ���t���[���ڂ�
    * @param mat �s��l
    */
    void setKeyFrame(int frame, int bone, const Math::Matrix4x4& mat);
    /**
    * @brief �L�[�t���[���ł̍s��̒ǉ�
    * @param mat �s��l
    * @details �O�ɒǉ������L�[�t���[����1�t���[����̍s���ݒ�ł���
    */
    void addKeyFrame(const Math::Matrix4x4& mat);
    /**
    * @brief �t���[���ɑ΂���s���Ԃ�
    */
    const Math::Matrix4x4& getKeyFrame(int frame, int bone);
    /**
    * @brief �L�[�t���[������Ԃ�
    */
    int getKeyFrameNum() const { return mKeyFrameNum; }
private:
    int mKeyFrameNum; //!< �L�[�t���[����
    std::vector<std::vector<Math::Matrix4x4>> mKeyFrames;
    //std::vector<Math::Matrix4x4> mKeyFrames; //!< �L�[�t���[�����Ƃ̍s��
};

} //Graphics 
} //Framework 
