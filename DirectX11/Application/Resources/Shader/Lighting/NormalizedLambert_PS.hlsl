#ifndef INCLUDE_LIGHTING_NORMALIZEDLAMBERT_PS_HLSL
#define INCLUDE_LIGHTING_NORMALIZEDLAMBERT_PS_HLSL

#include "../Utility/ShaderDefine.hlsli"
#define PI 3.1415926535f

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
};

float3 calcLam(float3 dif, float3 L, float3 N)
{
    return dif * max(dot(N, L), 0.0f) * (1.0f / PI);
}

float4 main(PSInput input) : SV_TARGET
{
    float4 sampleColor = float4(0.8f, 0.8f, 0.8f, 1.0f);
    float3 N = normalize(input.normal);
    float3 L = normalize(light.dirLight.direction.xyz);
    float3 dif = calcLam(sampleColor.rgb * light.dirLight.color.rgb, L, N);

    return float4(dif.xyz, 1.0f);
}

#endif // INCLUDE_LIGHTING_NORMALIZEDLAMBERT_PS_HLSL