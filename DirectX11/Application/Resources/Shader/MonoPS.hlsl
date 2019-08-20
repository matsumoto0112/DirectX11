#include "ShaderDefine.hlsli"
Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

float4 main(PS_IN IN) : SV_TARGET
{
    float4 c = tex.Sample(samLinear, IN.Tex);
    float gray = c.r * 0.3 + c.g * 0.6 + c.b * 0.1;
    return float4(gray, gray, gray, c.a);
}