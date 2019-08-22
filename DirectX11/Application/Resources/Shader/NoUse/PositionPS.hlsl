#include "ShaderDefine.hlsli"

struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

float4 main(PS_IN IN) : SV_TARGET
    {
    return color;
}