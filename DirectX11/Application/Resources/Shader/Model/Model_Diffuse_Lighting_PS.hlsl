Texture2D tex : register(t2);
SamplerState samLinear : register(s0);

#include "../Utility/ShaderDefine.hlsli"

struct ps_input
{
    float4 position : SV_POSITION;
    float4 WPosition : WORLDPOS;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 color : COLOR;
};

float4 main(ps_input input) : SV_TARGET
{
    float3 nor = normalize(input.normal.xyz);
    float3 rgb = 0;
    int i = 0;
    for (i = 0; i < MAX_DIRECTIONALLIGHT; ++i)
    {
        float l = saturate(dot(nor, -dirLights[i].dir));
        rgb += l * dirLights[i].colDirLight.rgb;
    }

    for (i = 0; i < MAX_POINTLIGHT; ++i)
    {
        float3 pDir = pLights[i].posPLight.xyz - input.WPosition.xyz;
        float r = length(pDir);
        pDir = normalize(pDir);
        rgb += pLights[i].colPLight.rgb
            * saturate(pLights[i].attPLight.z * r + pLights[i].attPLight.w)
            * saturate(dot(pDir, nor));
    }
    float4 o = float4(rgb, 1.0f) * tex.Sample(samLinear, input.uv);
    o *= input.color;
    o *= color;
    return o;
}