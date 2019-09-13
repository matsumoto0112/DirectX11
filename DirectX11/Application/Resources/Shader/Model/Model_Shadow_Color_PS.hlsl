#include "../Utility/ShaderDefine.hlsli"
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

struct ps_input
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
    float4 ShadowMapTex : TEXCOORD0;
};

/**
* @brief ”äŠrŠÖ”
* @param z z’l
* @param threshold è‡’l
* @param z‚ªè‡’l‚ð’´‚¦‚Ä‚¢‚½‚ç0
*/
float cmp(float z, float threshold)
{
    return z - threshold > 0 ? 1 : 0;
}

float4 main(ps_input input) : SV_TARGET
{
    float zValue = input.ShadowMapTex.z / input.ShadowMapTex.w;

    float2 texCoord;
    texCoord.x = (1.0f + input.ShadowMapTex.x / input.ShadowMapTex.w) * 0.5f;
    texCoord.y = (1.0f - input.ShadowMapTex.y / input.ShadowMapTex.w) * 0.5f;

    float z = tex2.Sample(samLinear, texCoord).x;
    if (zValue > z + 0.005f)
    {
        input.color.rgb *= 0.5f;
    }
    input.color.rgb *= color;
    input.color.a = color.a;
    return input.color;
}