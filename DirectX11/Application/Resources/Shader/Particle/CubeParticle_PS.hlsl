#include "../Utility/ShaderDefine.hlsli"

struct ps_input
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 main(ps_input input) : SV_TARGET
{
    float4 o = input.color;
    o *= color;
    clip(o.a - EPSILON);
    return o;
}