#pragma once

#include <memory>
#include "Framework/Graphics/Buffer/IndexBuffer.h"
#include "Framework/Graphics/Buffer/VertexBuffer.h"
#include "Framework/Graphics/ConstantBuffer/MaterialCBufferStruct.h"
#include "Framework/Graphics/Shader/Effect.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/Vertex/Vertex.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {
/**
* @class Model
* @brief ���f���Ǘ��N���X
*/
class Model {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Model(std::shared_ptr<VertexBuffer> vertexBuffer,
        std::shared_ptr<IndexBuffer> indexBuffer,
        std::shared_ptr<Effect> effect);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Model();
    /**
    * @brief �`�悷��
    */
    virtual void draw(const Utility::Transform& transform);
protected:
    std::shared_ptr<VertexBuffer> mVertexBuffer; //!< ���_�o�b�t�@
    std::shared_ptr<IndexBuffer> mIndexBuffer; //!< �C���f�b�N�X�o�b�t�@
    PROPERTY_POINTER(std::shared_ptr<Effect>, mEffect, Effect);
};

} //Graphics 
} //Framework 
