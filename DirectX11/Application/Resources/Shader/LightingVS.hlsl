#include "ShaderDefine.hlsli"

struct VS_IN
{
    float4 Pos : POSITION;
    float3 Nor : NORMAL;
    float2 Tex : TEXCOORD0;
    float4 Col : COLOR;
};

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float4 WPos : WORLDPOS;
    float3 Nor : NORMAL;
    float4 Col : COLOR;
    float2 Tex : TEXCOORD0;
};

PS_IN main(VS_IN IN)
{
    PS_IN o = (PS_IN) 0;
    o.Pos = mul(IN.Pos, mat.world);
    o.WPos = o.Pos;
    o.Pos = mul(o.Pos, mat.view);
    o.Pos = mul(o.Pos, mat.proj);
    o.Nor = mul(IN.Nor, (float3x3)mat.world);
    o.Col = IN.Col;
    o.Tex = IN.Tex * float2(uv.width, uv.height) + float2(uv.left, uv.top);
    return o;
}
