#ifndef INCLUDE_SHADOWMAP_SHADOWMAP_VS_HLSL
#define INCLUDE_SHADOWMAP_SHADOWMAP_VS_HLSL

#include "../Utility/ShaderDefine.hlsli"

struct VSInput
{
    float4 pos : POSITION;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float4 ZCalc : TEXCOORD0;
};

PSInput main(VSInput input)
{
    PSInput o = (PSInput) 0;
    o.pos = mul(input.pos, WORLD_VIEW_PROJECTION_3D());
    o.ZCalc = mul(input.pos, mat3D.world);
    o.ZCalc = mul(o.ZCalc, lightMat.view);
    o.ZCalc = mul(o.ZCalc, lightMat.proj);
    return o;
}

#endif // INCLUDE_SHADOWMAP_SHADOWMAP_VS_HLSL