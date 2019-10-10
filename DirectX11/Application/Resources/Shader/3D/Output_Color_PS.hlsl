#include "../Utility/ShaderDefine.hlsli"

struct ps_input
{
    float4 pos : SV_POSITION;
};

float4 main(ps_input input) : SV_TARGET
{
    float4 o = color;
    //return o;
    return float4(1.0f, 0.0f, 0.0f, 1.0f);

}