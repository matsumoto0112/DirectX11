#pragma once

namespace Framework {
namespace Graphics {

/**
* @class IDrawable
* @brief �`��\�I�u�W�F�N�g
*/
class IDrawable {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IDrawable() = default;
    /**
    * @brief �`�揈��
    */
    virtual void draw() = 0;
};

} //Graphics 
} //Framework 