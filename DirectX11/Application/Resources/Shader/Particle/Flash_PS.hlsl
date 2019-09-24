#include "../Utility/ShaderDefine.hlsli"
Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

float4 main(const PSInput input) : SV_TARGET
{
    float4 o = tex.Sample(samLinear, input.uv);
    o *= input.color;
    o *= color;
    clip(o.a - EPSILON);
    return o;
}