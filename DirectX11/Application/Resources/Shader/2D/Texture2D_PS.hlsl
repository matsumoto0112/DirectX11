//Texture2D tex : register(t0);
//SamplerState samLinear : register(s0);

#include "../Utility/ShaderDefine.hlsli"

struct ps_input
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

//float4 main(ps_input input) : SV_TARGET
//{
//    float4 o = tex.Sample(samLinear, input.uv);
//    o *= color;
//    clip(o.a - EPSILON);
//    return o;
//}

Texture2D<float> tex : register(t0);
SamplerState samplerState = sampler_state
{
    Texture = <tex>;
    MinLOD = 0.0f;
};

float4 main(ps_input input) : SV_TARGET
{
    float dep = tex.Sample(samplerState, input.uv);
    clip(1.0f - dep - EPSILON);
    return float4(dep, 0.0f, 0.0f, 1.0f);
}