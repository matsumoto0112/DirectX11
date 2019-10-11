#pragma once
#include <memory>
#include "Framework/Graphics/Renderer/AlphaBlend.h"
#include "Framework/Graphics/Renderer/RasterizerState.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Pipeline
* @brief 描画パイプライン管理クラス
*/
class Pipeline {
public:
    /**
    * @brief コンストラクタ
    */
    Pipeline(std::shared_ptr<AlphaBlend> alphaBlend,
        std::shared_ptr<RasterizerState> rasterizer);
    /**
    * @brief デストラクタ
    */
    virtual ~Pipeline();
    /**
    * @brief コンテキストの状態をクリアする
    */
    virtual void clearState();
    /**
    * @brief 描画パイプラインをセットする
    */
    virtual void setPipeline();
private:
    PROPERTY_POINTER(std::shared_ptr<AlphaBlend>, mAlphaBlend, AlphaBlend);
    PROPERTY_POINTER(std::shared_ptr<RasterizerState>, mRasterizer, RasterizerState);
};

} //Graphics 
} //Framework 