Texture2D tex : register(t0);
Texture2D ambTex : register(t1);
Texture2D difTex : register(t2);
Texture2D specTex : register(t3);
SamplerState samLinear : register(s0);


#define EPSILON 1e-6
#include "ShaderDefine.hlsli"

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float4 WPos : WORLDPOS;
    float3 Nor : NORMAL;
    float4 Col : COLOR;
    float2 Tex : TEXCOORD0;
};

float4 main(PS_IN IN) : SV_TARGET
{
    float3 nor = normalize(IN.Nor.xyz);
    float3 rgb = 0;
    int i = 0;
    for (i = 0; i < MAX_DIRECTIONALLIGHT; ++i)
    {
        float l = saturate(dot(nor, dirLights[i].dir));
        rgb += l * dirLights[i].colDirLight.rgb;
    }

    for (i = 0; i < MAX_POINTLIGHT; ++i)
    {
        float3 pDir = pLights[i].posPLight.xyz - IN.WPos.xyz;
        float r = length(pDir);
        pDir = normalize(pDir);
        rgb += pLights[i].colPLight.rgb
            * saturate(pLights[i].attPLight.z * r + pLights[i].attPLight.w)
            * saturate(dot(pDir, nor));
    }
    float4 o = float4(rgb, 1.0f) * difTex.Sample(samLinear, IN.Tex);
    return o;
}