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
    float4 ShadowMapTex : TEXCOORD1;
};

ps_input main(vs_input input)
{
    ps_input o = (ps_input) 0;
    o.position = mul(input.position, mat.world);
    o.position = mul(o.position, mat.view);
    o.position = mul(o.position, mat.proj);

    o.ShadowMapTex = o.position;
    return o;
}
