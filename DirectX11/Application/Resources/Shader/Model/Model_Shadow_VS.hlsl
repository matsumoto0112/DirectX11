#include "../Utility/ShaderDefine.hlsli"

cbuffer LIGHT : register(b10)
{
    matrix lightView;
    matrix lightProj;
    float3 lightPosition;
    float padding;
};

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
    float4 lightViewPosition : TEXCOORD1;
    float3 lightPos : TEXCOORD2;
};

ps_input main(vs_input input)
{
    ps_input o = (ps_input) 0;
    o.position = mul(input.position, mat.world);
    o.position = mul(o.position, mat.view);
    o.position = mul(o.position, mat.proj);

    o.lightViewPosition = mul(input.position, mat.world);
    o.lightViewPosition = mul(o.lightViewPosition, lightView);
    o.lightViewPosition = mul(o.lightViewPosition, lightProj);

    o.uv = input.uv;

    o.normal = mul(input.normal, (float3x3) mat.world);
    o.normal = normalize(o.normal);

    float4 worldPos = mul(input.position, mat.world);
    o.lightPos = lightPosition.xyz - worldPos.xyz;
    o.lightPos = normalize(o.lightPos);

    return o;
}
