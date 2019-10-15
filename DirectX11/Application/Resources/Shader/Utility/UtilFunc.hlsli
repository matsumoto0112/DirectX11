#ifndef INCLUDE_UTILITY_UTILFUNC_HLSLI
#define INCLUDE_UTILITY_UTILFUNC_HLSLI

float4 convertColorFromInt4(int4 rgba)
{
    return rgba / 255.0;
}

float3 convertColorFromInt3(int3 rgb)
{
    return rgb / 255.0;
}

#endif // INCLUDE_UTILITY_UTILFUNC_HLSLI