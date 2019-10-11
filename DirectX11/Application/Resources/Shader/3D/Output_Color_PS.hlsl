#include "../Utility/ShaderDefine.hlsli"

struct ps_input
{
    float4 pos : SV_POSITION;
};

float4 main(ps_input input) : SV_TARGET
{
    float4 o = color;
    return o;
}