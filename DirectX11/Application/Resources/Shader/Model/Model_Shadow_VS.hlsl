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
    float4 color : COLOR0;
    float4 ShadowMapTex : TEXCOORD0;
};

ps_input main(vs_input input)
{
    ps_input o = (ps_input) 0;
    o.position = mul(input.position, mat.world);
    o.position = mul(o.position, mat.view);
    o.position = mul(o.position, mat.proj);

    o.ShadowMapTex = mul(input.position, mat.world);
    o.ShadowMapTex = mul(o.ShadowMapTex, lightMat.view);
    o.ShadowMapTex = mul(o.ShadowMapTex, lightMat.proj);

    float3 N = normalize(mul(input.normal, (float3x3) mat.world));
    float3 dir = float3(lightMat.view._13, lightMat.view._23, lightMat.view._33);
    float3 lightDirect = normalize(dir);
    o.color = float4(255.0f / 255, 233.0f / 255, 64.0f / 255, 1.0f) * (0.3 + dot(N, -lightDirect) * (1.0f - 0.3f));

    return o;
}
