#pragma once
#include "Source/GameObject/GameObject3D.h"

/**
* @class Wall
* @brief ��
*/
class Wall :public GameObject3D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Wall(const Framework::Utility::Transform& transform);
    /**
    * @brief �f�X�g���N�^
    */
    ~Wall();
private:
};