#include "../Utility/ShaderDefine.hlsli"

Texture2D<float> depth : register(t0);
SamplerState samplerState : register(s0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float4 ZCalc : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float ZValue = input.ZCalc.z / input.ZCalc.w;
    float2 uv;
    uv.x = (1.0f + input.ZCalc.x / input.ZCalc.w) * 0.5f;
    uv.y = (1.0f - input.ZCalc.y / input.ZCalc.w) * 0.5f;
    float dep = depth.Sample(samplerState, uv);

    float4 o = color;
    if (ZValue > dep + 0.005f)
    {
        o.rgb *= 0.5f;
    }
    return o;
}