#pragma once
#include "Source/GameObject/GameObject3D.h"

/**
* @class Floor
* @brief ���I�u�W�F�N�g
*/
class Floor :public GameObject3D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Floor(const Framework::Utility::Transform& transform);
    /**
    * @brief �f�X�g���N�^
    */
    ~Floor();
private:

};