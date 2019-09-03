#pragma once
#include "Source/GameObject/GameObject3D.h"

namespace Framework {
namespace Graphics {
class Cube;
} //Graphics 
} //Framework 

class IMainSceneMediator;

/**
* @class Wall
* @brief ��
*/
class Wall :public GameObject3D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Wall(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~Wall();

    virtual void draw() override;
private:
    std::unique_ptr<Framework::Graphics::Cube> mCube;
    Framework::Utility::Transform mCubeTransform;
};