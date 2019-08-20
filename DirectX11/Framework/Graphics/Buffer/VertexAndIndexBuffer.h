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
* @brief ���_�E�C���f�b�N�X�o�b�t�@���܂Ƃ߂��N���X
*/
class VertexAndIndexBuffer {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @tparam vertices ���_�f�[�^
    * @param indices �C���f�b�N�X�f�[�^
    * @param topology �v���~�e�B�u�g�|���W�[�̎��
    */
    template<class T>
    VertexAndIndexBuffer(const std::vector<T>& vertices,
        const std::vector<WORD>& indices,
        PrimitiveTopology topology);
    /**
    * @brief �f�X�g���N�^
    */
    ~VertexAndIndexBuffer();

    /**
    * @brief �`�悷��
    * @details �`��O�ɕ`��ɕK�v�ȃf�[�^�𑗂��Ă����K�v������
    */
    void render();
private:
    std::unique_ptr<VertexBuffer> mVertexBuffer; //!< ���_�o�b�t�@
    std::unique_ptr<IndexBuffer> mIndexBuffer; //!< �C���f�b�N�X�o�b�t�@
};

template<class T>
inline VertexAndIndexBuffer::VertexAndIndexBuffer(const std::vector<T>& vertices,
    const std::vector<WORD>& indices,
    PrimitiveTopology topology)
    :mVertexBuffer(std::make_unique<VertexBuffer>(vertices)),
    mIndexBuffer(std::make_unique<IndexBuffer>(indices, topology)) {}

} //Graphics 
} //Framework 