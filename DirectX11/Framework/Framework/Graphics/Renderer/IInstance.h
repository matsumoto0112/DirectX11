#pragma once
#include <memory>
#include "Framework/Utility/Transform.h"
#include "Framework/Graphics/Buffer/VertexAndIndexBuffer.h"

namespace Framework {
namespace Graphics {

/**
* @class IInstance
* @brief レンダリングインスタンス基底クラス
*/
class IInstance {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IInstance() {};
    /**
    * @brief 描画する
    * @param transform オブジェクトのトランスフォーム
    */
    virtual void render(const Utility::Transform& transform);
protected:
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer; //!< 頂点・インデックスバッファ
};

} //Graphics 
} //Framework 