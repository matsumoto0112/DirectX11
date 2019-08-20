#pragma once
#include "Math/Vector2.h"

namespace Framework {

namespace Math {
class Matrix4x4;
} //Math 

namespace Utility {

/**
* @class Transform2D
* @brief 2D�g�����X�t�H�[��
*/
class Transform2D
{
public:
    /**
    * @brief �R���X�g���N�^
    * @param position ���W
    * @param scale �傫��
    * @param rotate ��]
    */
    Transform2D(const Math::Vector2& position, const Math::Vector2& scale, float rotate);
    /**
    * @brief �f�X�g���N�^
    */
    ~Transform2D();
    /**
    * @brief ���W�̐ݒ�
    */
    void setPosition(const Math::Vector2& position);
    /**
    * @brief ���W�̎擾
    */
    const Math::Vector2& getPosition() const;
    /**
    * @brief �傫���̐ݒ�
    */
    void setScale(const Math::Vector2& scale);
    /**
    * @brief �傫���̎擾
    */
    const Math::Vector2& getScale() const;
    /**
    * @brief ��]�̐ݒ�
    */
    void setRotate(float rotate);
    /**
    * @brief ��]�̎擾
    */
    float getRotate() const;
    /**
    * @brief ���W�ϊ��s��̍쐬
    */
    Math::Matrix4x4 createSRTMatrix() const;
    /**
    * @brief ���[�J�����W�ϊ��s��̍쐬
    */
    Math::Matrix4x4 createLocalSRTMatrix() const;
    /**
    * @brief �y�A�����g�̐ݒ�
    */
    void setParent(Transform2D* parent);
    /**
    * @brief �y�A�����g�̎擾
    */
    const Transform2D* getParent() const;
private:
    Math::Vector2 mPosition; //!< ���W
    Math::Vector2 mScale; //!< �傫��
    float mRotate; //!< ��]
    Transform2D* mParent; //!< �e��Transform
};
} //Utility 
} //Framework 
