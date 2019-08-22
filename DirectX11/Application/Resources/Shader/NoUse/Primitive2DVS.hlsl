#include "ShaderDefine.hlsli"

struct VS_Input
{
    float4 Pos : POSITION;
};

struct PS_Input
{
    float4 Pos : SV_POSITION;
};

PS_Input main(VS_Input IN)
{
    PS_Input o = (PS_Input) 0;
    o.Pos = mul(IN.Pos, mat.world);
    o.Pos = mul(o.Pos, mat.view);
    o.Pos = mul(o.Pos, mat.proj);
    return o;
}