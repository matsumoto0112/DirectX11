#pragma once

#include <memory>
#include "Framework/Graphics/Buffer/IndexBuffer.h"
#include "Framework/Graphics/Buffer/VertexBuffer.h"
#include "Framework/Graphics/Renderer/IDrawable.h"
#include "Framework/Graphics/Shader/Effect.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/Vertex/Vertex.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/Transform.h"
#include "Framework/Graphics/Material/ModelMaterial.h"

namespace Framework {
namespace Graphics {
/**
* @class Model
* @brief ���f���Ǘ��N���X
*/
class Model : public IDrawable {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Model(std::shared_ptr<VertexBuffer> vertexBuffer,
        std::shared_ptr<IndexBuffer> indexBuffer,
        std::shared_ptr<Effect> effect,
        std::shared_ptr<IMaterial> material);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Model();
    /**
    * @brief �`�悷��
    */
    virtual void draw() override;
protected:
    std::shared_ptr<VertexBuffer> mVertexBuffer; //!< ���_�o�b�t�@
    std::shared_ptr<IndexBuffer> mIndexBuffer; //!< �C���f�b�N�X�o�b�t�@
    PROPERTY_POINTER(std::shared_ptr<IMaterial>, mMaterial, Material);
};

} //Graphics 
} //Framework 
