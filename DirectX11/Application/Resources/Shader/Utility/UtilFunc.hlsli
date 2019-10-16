#ifndef INCLUDE_UTILITY_UTILFUNC_HLSLI
#define INCLUDE_UTILITY_UTILFUNC_HLSLI

#include "ShaderDefine.hlsli"

float4 convertColorFromInt4(int4 rgba)
{
    return rgba / 255.0;
}

float3 convertColorFromInt3(int3 rgb)
{
    return rgb / 255.0;
}

float4 calcLightPos()
{
    float x = -dot(lightMat.view._m00_m01_m02_m03, lightMat.view._m30_m31_m32_m33);
    float y = -dot(lightMat.view._m10_m11_m12_m13, lightMat.view._m30_m31_m32_m33);
    float z = -dot(lightMat.view._m20_m21_m22_m23, lightMat.view._m30_m31_m32_m33);
    return float4(x, y, z, 1.0);
}

#endif // INCLUDE_UTILITY_UTILFUNC_HLSLI