#include "../Utility/ShaderDefine.hlsli"

struct vs_input
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct ps_input
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

ps_input main(vs_input input)
{
    ps_input o = (ps_input) 0;
    o.position = mul(input.position, mat.world);
    o.position = mul(o.position, mat.view);
    o.position = mul(o.position, mat.proj);
    o.uv = input.uv * float2(uv.width, uv.height) + float2(uv.left, uv.top);
    return o;
}