Texture2D tex : register(t2);
SamplerState samLinear : register(s0);

#include "../Utility/ShaderDefine.hlsli"

struct ps_input
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 color : COLOR;
};

struct ps_output
{
    float4 target0 : SV_TARGET0;
    float4 target1 : SV_TARGET1;
    float4 target2 : SV_TARGET2;
    float4 target3 : SV_TARGET3;
};

ps_output main(ps_input input)
{
    ps_output o = (ps_output) 0;
    float4 outColor = tex.Sample(samLinear, input.uv);
    outColor *= input.color;
    outColor *= color;
    o.target0 = float4(outColor.r, 0.0f, 0.0f, outColor.r);
    o.target1 = float4(0.0f, outColor.g, 0.0f, outColor.g);
    o.target2 = float4(0.0f, 0.0f, outColor.b, outColor.b);
    o.target3 = float4(1 - outColor.a, 1 - outColor.a, 1 - outColor.a, 1.0f);
    return o;
}