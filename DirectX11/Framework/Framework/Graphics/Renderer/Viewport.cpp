#include "Viewport.h"

namespace Framework {
    namespace Graphics {

        Viewport::Viewport(const Math::Rect& rect) {
            mViewport.TopLeftX = rect.getX();
            mViewport.TopLeftY = rect.getY();
            mViewport.Width = rect.getWidth();
            mViewport.Height = rect.getHeight();
            mViewport.MinDepth = 0.0f;
            mViewport.MaxDepth = 1.0f;
        }

        Viewport::~Viewport() { }

        void Viewport::set(ID3D11DeviceContext* context) {
            context->RSSetViewports(1, &mViewport);
        }

        void Viewport::clearState(ID3D11DeviceContext* context) {
            context->RSSetViewports(1, nullptr);
        }

    } //Graphics 
} //Framework 
