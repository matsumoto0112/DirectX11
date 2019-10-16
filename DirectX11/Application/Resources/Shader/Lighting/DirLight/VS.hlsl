#ifndef INCLUDE_LIGHTING_DIRLIGHT_VS_HLSL
#define INCLUDE_LIGHTING_DIRLIGHT_VS_HLSL

#include "../../Utility/ShaderDefine.hlsli"

struct VSInput
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
};

PSInput main(VSInput input)
{
    PSInput o = (PSInput) 0;
    o.pos = mul(input.pos, WORLD_VIEW_PROJECTION_3D());
    o.normal = mul(input.normal, (float3x3) mat3D.world);
    return o;
}

#endif // INCLUDE_LIGHTING_DIRLIGHT_VS_HLSL
