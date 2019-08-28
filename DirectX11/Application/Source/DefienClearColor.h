#pragma once

#include "Framework/Graphics/Color4.h"

class DefineClearColor {
public:
    static Framework::Graphics::Color4 ClearRenderTargetColor;
    static const Framework::Graphics::Color4 ClearShadowMapColor;
    static void setColor(Framework::Graphics::Color4 c) {
        ClearRenderTargetColor = c;
    }
    static Framework::Graphics::Color4 getColor() { return ClearRenderTargetColor; }
};