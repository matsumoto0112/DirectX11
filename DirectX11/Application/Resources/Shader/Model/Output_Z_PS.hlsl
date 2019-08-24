#include "../Utility/ShaderDefine.hlsli"

struct ps_input
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 color : COLOR;
    float4 ShadowMapTex : TEXCOORD1;
};

float4 main(ps_input input) : SV_TARGET
{
    float4 o = input.ShadowMapTex.z / input.ShadowMapTex.w;
    return o;
}