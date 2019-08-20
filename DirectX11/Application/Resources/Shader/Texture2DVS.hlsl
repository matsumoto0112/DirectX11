#include "ShaderDefine.hlsli"

struct VS_IN
{
    float4 Pos : POSITION0;
    float2 Tex : TEXCOORD0;
};

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

PS_IN main(VS_IN IN)
{
    PS_IN o = (PS_IN) 0;
    o.Pos = mul(IN.Pos, mat.world);
    o.Pos = mul(o.Pos, mat.view);
    o.Pos = mul(o.Pos, mat.proj);
    o.Tex = IN.Tex * float2(uv.width, uv.height) + float2(uv.left, uv.top);
    return o;
}