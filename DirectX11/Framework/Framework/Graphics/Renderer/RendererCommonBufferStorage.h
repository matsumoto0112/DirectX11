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
* @brief �`��p���ʃo�b�t�@�ێ��N���X
*/
class RendererCommonBufferStorage : public Utility::Singleton<RendererCommonBufferStorage> {
public:
    /**
    * @brief �R���X�g���N�^
    */
    RendererCommonBufferStorage();
    /**
    * @brief �f�X�g���N�^
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