#include "VertexBuffer.h"

namespace Framework {
    namespace Graphics {
        //�f�X�g���N�^
        VertexBuffer::~VertexBuffer() { }

        //�f�[�^���Z�b�g����
        void VertexBuffer::set(ID3D11DeviceContext * context) {
            context->IASetVertexBuffers(0, 1, mBuffer.GetAddressOf(), &mStride, &mOffset);
        }
    } //Graphics 
} //Framework 