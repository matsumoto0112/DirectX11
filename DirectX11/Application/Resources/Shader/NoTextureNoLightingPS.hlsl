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
    float4 o = IN.Col;
    o *= material.diffuse;
    o *= color;
    return o;
}