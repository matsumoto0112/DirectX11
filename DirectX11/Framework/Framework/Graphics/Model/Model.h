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
* @brief モデル管理クラス
*/
class Model : public IDrawable {
public:
    /**
    * @brief コンストラクタ
    */
    Model(std::shared_ptr<VertexBuffer> vertexBuffer,
        std::shared_ptr<IndexBuffer> indexBuffer,
        std::shared_ptr<Effect> effect,
        std::shared_ptr<IMaterial> material);
    /**
    * @brief デストラクタ
    */
    virtual ~Model();
    /**
    * @brief 描画する
    */
    virtual void draw() override;

    /**
    * @brief マテリアルをセットする
    */
    void setMaterial(std::shared_ptr<IMaterial> newMaterial) { mMaterial = newMaterial; }

    /**
    * @brief マテリアルを取得する
    * @tparam T マテリアルの型
    * @details マテリアルがTに変換できなければコンパイルエラーとなる
    */
    template <class T>
    T* getMaterial() const;
protected:
    std::shared_ptr<VertexBuffer> mVertexBuffer; //!< 頂点バッファ
    std::shared_ptr<IndexBuffer> mIndexBuffer; //!< インデックスバッファ
    std::shared_ptr<IMaterial> mMaterial;
};

template<class T>
inline T* Model::getMaterial() const {
    return static_cast<T*>(mMaterial.get());
}

} //Graphics 
} //Framework 
