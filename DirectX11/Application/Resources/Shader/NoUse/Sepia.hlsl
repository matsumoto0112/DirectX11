#include "ShaderDefine.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float3 mono = float3(0.298912, 0.586611, 0.114478);
float3 sepia = float3(1.07, 0.74, 0.43);

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

float4 main(const PS_IN IN) : SV_TARGET
{
    float4 o = tex.Sample(samLinear, IN.Tex);
    o.rgb = dot(o.rgb, mono) * o.a;
    o.rbg *= sepia;

    return o;
}