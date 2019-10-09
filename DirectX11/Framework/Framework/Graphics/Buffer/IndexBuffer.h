#pragma once

#include <vector>
#include <d3d11.h>
#include <memory>
#include <wrl/client.h>
#include "Framework/Graphics/Buffer/IndexBufferBindData.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

/**
* @class IndexBuffer
* @brief インデックスバッファ管理クラス
*/
class IndexBuffer {
public:
    /**
    * @brief コンストラクタ
    * @param indices インデックスデータ
    * @param topology プリミティブトポロジーの種類
    */
    IndexBuffer(const std::vector<UINT>& indices, PrimitiveTopology topology);
    /**
    * @brief デストラクタ
    */
    ~IndexBuffer();
    /**
    * @brief インデックスデータのセット
    */
    void setData();
    /**
    * @brief 描画指令を送る
    */
    void drawCall();
private:
    /**
    * @brief インデックスデータの設定
    * @param indices インデックスデータ
    */
    void setBuffer(const std::vector<UINT>& indices, PrimitiveTopology topology);
private:
    std::unique_ptr<IndexBufferBindData> mData; //!< インデックスバッファのデータ
    UINT mIndexCount; //!< 頂点数
};

} //Graphics 
} //Framework 