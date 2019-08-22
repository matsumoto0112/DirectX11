Texture2D tex : register(t0);
Texture2D ambTex : register(t1);
Texture2D difTex : register(t2);
Texture2D specTex : register(t3);
SamplerState samLinear : register(s0);

#define EPSILON 1e-6
#include "ShaderDefine.hlsli"

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float3 Nor : NORMAL;
    float2 Tex : TEXCOORD0;
    float4 Col : COLOR;
};

float4 main(PS_IN IN) : SV_TARGET
{
    float4 o = difTex.Sample(samLinear, IN.Tex);
    o = float4(1.0f, 0.0f, 0.0f, 1.0f);
    //o = float4(GetN(IN.Nor.x), GetN(IN.Nor.y), GetN(IN.Nor.z), 1.0f);
    //clip(o.a - EPSILON);
    return o;
}