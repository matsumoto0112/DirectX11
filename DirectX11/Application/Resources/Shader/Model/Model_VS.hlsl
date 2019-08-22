#include "../Utility/ShaderDefine.hlsli"

struct vs_input
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

struct ps_input
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

ps_input main(vs_input input)
{
    ps_input o = (ps_input) 0;
    o.position = mul(input.position, mat.world);
    o.position = mul(o.position, mat.view);
    o.position = mul(o.position, mat.proj);
    o.normal = mul(input.normal, (float3x3) mat.world);
    o.color = input.color;
    o.uv = input.uv * float2(uv.width, uv.height) + float2(uv.left, uv.top);
    return o;

}
