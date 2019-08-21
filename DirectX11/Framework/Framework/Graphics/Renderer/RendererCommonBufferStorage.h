#pragma once
#include <unordered_map>
#include <memory>
#include "Framework/Utility/Singleton.h"
#include "Framework/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Framework/Graphics/Renderer/RendererInstanceType.h"

namespace Framework {
namespace Graphics {

/**
* @class RendererCommonBufferStorage
* @brief 描画用共通バッファ保持クラス
*/
class RendererCommonBufferStorage : public Utility::Singleton<RendererCommonBufferStorage> {
public:
    /**
    * @brief コンストラクタ
    */
    RendererCommonBufferStorage();
    /**
    * @brief デストラクタ
    */
    ~RendererCommonBufferStorage();

    void registerBuffer(RendererInstanceType type, std::shared_ptr<VertexAndIndexBuffer> buffer);
    bool isRegistered(RendererInstanceType type) const;
    void clearBuffer();
    std::shared_ptr<VertexAndIndexBuffer> getBuffer(RendererInstanceType type);
private:
    std::unordered_map<RendererInstanceType, std::shared_ptr<VertexAndIndexBuffer>> mCommonBuffers;
};

} //Graphics 
} //Framework