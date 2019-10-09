#pragma once

#include <memory>
#include "Framework/Graphics/Vertex/Vertex.h"
#include "Framework/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/ConstantBuffer/MaterialCBufferStruct.h"
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
    Model(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer,
        std::shared_ptr<VertexShader> vertexShader, std::shared_ptr<PixelShader> pixelShader);
    /**
    * @brief デストラクタ
    */
    virtual ~Model();
    /**
    * @brief 描画する
    */
    virtual void draw(const Utility::Transform& transform);
    /**
    * @brief 頂点シェーダーを取得する
    */
    std::shared_ptr<VertexShader> getVertexShader() const { return mVertexShader; }
    /**
    * @brief ピクセルシェーダーを取得する
    */
    std::shared_ptr<PixelShader> getPixelShader() const { return mPixelShader; }
    /**
    * @brief 頂点シェーダーを設定する
    * @param vertexShader 頂点シェーダー
    */
    void setVertexShader(std::shared_ptr<VertexShader> vertexShader) { mVertexShader = vertexShader; }
    /**
    * @brief ピクセルシェーダーを設定する
    * @param pixelShader ピクセルシェーダー
    */
    void setPixelShader(std::shared_ptr<PixelShader> pixelShader) { mPixelShader = pixelShader; }
protected:
    std::shared_ptr<VertexBuffer> mVertexBuffer;
    std::shared_ptr<IndexBuffer> mIndexBuffer;
    std::shared_ptr<VertexShader> mVertexShader;
    std::shared_ptr<PixelShader> mPixelShader;
};

} //Graphics 
} //Framework 
