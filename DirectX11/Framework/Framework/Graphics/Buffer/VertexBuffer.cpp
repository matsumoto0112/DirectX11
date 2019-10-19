#include "VertexBuffer.h"

namespace Framework {
    namespace Graphics {
        //デストラクタ
        VertexBuffer::~VertexBuffer() { }

        //データをセットする
        void VertexBuffer::set(ID3D11DeviceContext * context) {
            context->IASetVertexBuffers(0, 1, mBuffer.GetAddressOf(), &mStride, &mOffset);
        }
    } //Graphics 
} //Framework 