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
* @brief モデル管理クラス
*/
class Model {
public:
    /**
    * @brief コンストラクタ
    */
    Model(std::shared_ptr<VertexBuffer> vertexBuffer,
        std::shared_ptr<IndexBuffer> indexBuffer,
        std::shared_ptr<Effect> effect);
    /**
    * @brief デストラクタ
    */
    virtual ~Model();
    /**
    * @brief 描画する
    */
    virtual void draw(const Utility::Transform& transform);
protected:
    std::shared_ptr<VertexBuffer> mVertexBuffer; //!< 頂点バッファ
    std::shared_ptr<IndexBuffer> mIndexBuffer; //!< インデックスバッファ
    PROPERTY_POINTER(std::shared_ptr<Effect>, mEffect, Effect);
};

} //Graphics 
} //Framework 
