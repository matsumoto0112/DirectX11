Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

#define EPSILON 1e-6
#include "ShaderDefine.hlsli"

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

float4 main(PS_IN IN) : SV_TARGET
{
    float4 o = tex.Sample(samLinear, IN.Tex);
    o *= color;
    //����0�����Ȃ�`�悵�Ȃ��i�A���t�@�e�X�g�j
    clip(o.a - EPSILON);
    return o;
}