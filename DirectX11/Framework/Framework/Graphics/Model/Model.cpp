#include "Model.h"
#include "Framework/Define/Path.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"

namespace Framework {
namespace Graphics {

Model::Model(std::shared_ptr<VertexBuffer> vertexBuffer,
    std::shared_ptr<IndexBuffer> indexBuffer,
    std::shared_ptr<Effect> effect,
    std::shared_ptr<IMaterial> material)
    :IDrawable(effect), mVertexBuffer(vertexBuffer),
    mIndexBuffer(indexBuffer),
    mMaterial(material) { }

Model::~Model() { }

void Model::draw() {
    mEffect->set();
    mMaterial->set();
    mVertexBuffer->setData();
    mIndexBuffer->setData();
    mIndexBuffer->drawCall();
}

} //Graphics 
} //Framework 

