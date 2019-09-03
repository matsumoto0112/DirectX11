#pragma once
#include <memory>
#include "Framework/Utility/Transform.h"
#include "Framework/Graphics/Buffer/VertexAndIndexBuffer.h"

namespace Framework {
namespace Graphics {

/**
* @class IInstance
* @brief �����_�����O�C���X�^���X���N���X
*/
class IInstance {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IInstance() {};
    /**
    * @brief �`�悷��
    * @param transform �I�u�W�F�N�g�̃g�����X�t�H�[��
    */
    virtual void render(const Utility::Transform& transform);
protected:
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer; //!< ���_�E�C���f�b�N�X�o�b�t�@
};

} //Graphics 
} //Framework 