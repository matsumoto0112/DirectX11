#include "../Utility/ShaderDefine.hlsli"

Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);
SamplerState samplerState : register(s0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

float4 main(const PSInput input) : SV_TARGET
{
    float4 t0 = tex0.Sample(samplerState, input.uv);
    float4 t1 = tex1.Sample(samplerState, input.uv);

    float4 o = (t0 + t1) * 0.5f;
    return o;
}