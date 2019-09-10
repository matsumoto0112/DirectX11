#pragma once
#include "Framework/Utility/Property.h"
#include "Framework/Utility/Transform2D.h"

namespace UI {

/**
* @class IItem
* @brief UI�A�C�e���C���^�[�t�F�[�X
*/
class IItem {
public:
    /**
    * @brief �R���X�g���N�^
    */
    IItem(const Framework::Utility::Transform2D& transform) :
        mTransform(transform) {}
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IItem() = default;
    /**
    * @brief �`�揈��
    */
    virtual void render() = 0;
protected:
    PROPERTY(Framework::Utility::Transform2D, mTransform, Transform);
};

} //UI 