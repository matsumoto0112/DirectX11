#pragma once

#include <memory>
#include <vector>
#include <d3d11.h>
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Vertex/Vertex.h"

namespace Framework {
namespace Graphics {

class GraphicsDeviceManager;

/**
* @class VertexAndIndexBuffer
* @brief 頂点・インデックスバッファをまとめたクラス
*/
class VertexAndIndexBuffer {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @tparam vertices 頂点データ
    * @param indices インデックスデータ
    * @param topology プリミティブトポロジーの種類
    */
    template<class T>
    VertexAndIndexBuffer(const std::vector<T>& vertices,
        const std::vector<WORD>& indices,
        PrimitiveTopology topology);
    /**
    * @brief デストラクタ
    */
    ~VertexAndIndexBuffer();

    /**
    * @brief 描画する
    * @details 描画前に描画に必要なデータを送っておく必要がある
    */
    void render();
private:
    std::unique_ptr<VertexBuffer> mVertexBuffer; //!< 頂点バッファ
    std::unique_ptr<IndexBuffer> mIndexBuffer; //!< インデックスバッファ
};

template<class T>
inline VertexAndIndexBuffer::VertexAndIndexBuffer(const std::vector<T>& vertices,
    const std::vector<WORD>& indices,
    PrimitiveTopology topology)
    :mVertexBuffer(std::make_unique<VertexBuffer>(vertices)),
    mIndexBuffer(std::make_unique<IndexBuffer>(indices, topology)) {}

} //Graphics 
} //Framework 