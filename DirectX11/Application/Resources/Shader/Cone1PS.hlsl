Texture2D tex : register(t0);
Texture2D ambMap : register(t1);
Texture2D difMap : register(t2);
Texture2D bumpMap : register(t3);
SamplerState samLinear : register(s0);

#define EPSILON 1e-6
#include "ShaderDefine.hlsli"

struct PS_IN {
    float4 Pos : SV_POSITION;
    float3 Nor : NORMAL;
    float2 Tex : TEXCOORD0;
};

float4 main(PS_IN IN) : SV_TARGET
{
    float4 o = difMap.Sample(samLinear,IN.Tex) * material.diffuse;
    o = float4(1.0f, 0.0f, 0.0f, 1.0);
    //o = ambMap.Sample(samLinear, IN.Tex) * material.ambient;
    //o = bumpMap.Sample(samLinear, IN.Tex) * float4(1.0f, 1.0f, 1.0f, 1.0f);
    //o.a = material.alpha;
    //float4 o = tex.Sample(samLinear, IN.Tex);
    //o *= color;
    //αが0未満なら描画しない（アルファテスト）
    clip(o.a - EPSILON);
    return o;
}