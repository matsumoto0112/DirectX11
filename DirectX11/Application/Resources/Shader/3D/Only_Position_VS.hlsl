#include "../Utility/ShaderDefine.hlsli"

struct vs_input
{
    float4 pos : POSITION;
};

struct ps_input
{
    float4 pos : SV_POSITION;
};

ps_input main(vs_input input)
{
    ps_input o = (ps_input) 0;
    o.pos = mul(input.pos, MVP());
    return o;
}