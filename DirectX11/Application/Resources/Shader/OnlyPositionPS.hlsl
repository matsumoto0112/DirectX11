#include "ShaderDefine.hlsli"

struct PS_Input
{
    float4 pos : SV_POSITION;
};

float4 main(PS_Input IN) : SV_TARGET
{
    return color;
}