#include "ShaderDefine.hlsli"
Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

cbuffer CbBlur : register(b6)
{
    int sampleCount;
    float4 offset[16];
};

float4 main(PS_IN IN) : SV_TARGET
{
    float4 result = 0;

    for (int i = 0; i < sampleCount; ++i)
    {
        result += offset[i].z * tex.Sample(samLinear, IN.Tex + offset[i].xy);
    }
    result.w = 1.0f;
    return result;
}