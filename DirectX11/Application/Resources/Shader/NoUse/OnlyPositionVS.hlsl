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
    PS_Input result = (PS_Input) 0;
    result.Pos = mul(IN.Pos, mat.world);
    result.Pos = mul(result.Pos, mat.view);
    result.Pos = mul(result.Pos, mat.proj);
    return result;
}