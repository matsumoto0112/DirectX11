#include "ShaderDefine.hlsli"

Texture2D tex1 : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 getColor(Texture2D tex, float2 uv)
{
    float4 result = 0;
    const int off = 1;
    result += tex.SampleLevel(samLinear, uv, 0);
    return result;
}

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

float4 main(PS_IN IN) : SV_TARGET
{
    float4 c = 0;
    c += getColor(tex1, IN.Tex);
    c += getColor(tex2, IN.Tex);
    c.w = 1.0f;
    return c;
}