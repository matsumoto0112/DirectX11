#include "../Utility/ShaderDefine.hlsli"
Texture2D tex : register(t0);
SamplerState samLinear = sampler_state // サンプラーステート
{
    texture = (texShadowMap);
    AddressU = CLAMP;
    AddressV = CLAMP;
    AddressW = CLAMP;
    MIPFILTER = LINEAR;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
};

struct ps_input
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
    float4 ShadowMapTex : TEXCOORD0;
};

float4 main(ps_input input) : SV_TARGET
{
    float zValue = input.ShadowMapTex.z / input.ShadowMapTex.w;

    float2 texCoord;
    texCoord.x = (1.0f + input.ShadowMapTex.x / input.ShadowMapTex.w) * 0.5f;
    texCoord.y = (1.0f - input.ShadowMapTex.y / input.ShadowMapTex.w) * 0.5f;

    float z = tex.Sample(samLinear, texCoord).x;
    if (zValue > z + 0.005f)
    {
        input.color.rgb *= 0.5f;
    }
    return input.color;
}