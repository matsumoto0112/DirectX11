#pragma once
#include "Source/GameObject/GameObject.h"

namespace Framework {
namespace Graphics {
class Model;
} //Graphics 
} //Framework 

/**
* @class Wall
* @brief ��
*/
class Wall :public GameObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Wall(const Framework::Utility::Transform& transform);
    /**
    * @brief �f�X�g���N�^
    */
    ~Wall();
    virtual void update();
    virtual void draw();
private:
    std::shared_ptr<Framework::Graphics::Model> mModel;
};