#include "ShaderDefine.hlsli"

struct PS_Input
{
    float4 Pos : SV_POSITION;
};

float4 main() : SV_TARGET
{
    return color;
}