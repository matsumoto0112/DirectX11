#include "ShaderDefine.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

struct ps_input
{
    float4 pos : SV_POSITION;
    float3 nor : NORMAL;
    float2 tex : TEXCOORD0;
    float4 col : COLOR;
};

float4 main(ps_input input) : SV_TARGET
{
    float4 o = float4(0.0f, 1.0f, 0.0f, 1.0f);
    //return tex.Sample(samLinear, input.tex);
    return o;
}