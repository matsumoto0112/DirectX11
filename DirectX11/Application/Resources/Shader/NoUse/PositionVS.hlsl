#include "ShaderDefine.hlsli"

struct VS_IN
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD;
};
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

PS_IN main(VS_IN IN)
{
    PS_IN o = (PS_IN) 0;
    o.pos = mul(IN.pos, mat.world);
    o.pos = mul(o.pos, mat.view);
    o.pos = mul(o.pos, mat.proj);

    o.tex = IN.tex;
    return o;
}