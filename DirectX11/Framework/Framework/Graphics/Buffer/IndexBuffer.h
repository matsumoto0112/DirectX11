#pragma once

#include <vector>
#include <d3d11.h>
#include "Framework/Graphics/Buffer/PrimitiveTopology.h"

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
    ComPtr<ID3D11Buffer> mBuffer; //!< インデックスバッファ
    D3D11_PRIMITIVE_TOPOLOGY mTopology; //!< プリミティブトポロジーの種類
    UINT mIndexCount; //!< 頂点数
};

} //Graphics 
} //Framework 