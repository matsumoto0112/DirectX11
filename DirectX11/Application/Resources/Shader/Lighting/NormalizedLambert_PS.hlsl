#ifndef INCLUDE_LIGHTING_NORMALIZEDLAMBERT_PS_HLSL
#define INCLUDE_LIGHTING_NORMALIZEDLAMBERT_PS_HLSL

#define PI 3.1415926535f

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float3 lightDir : LIGHTDIR;
    float3 viewDir : VIEWDIR;
};

float3 calcLam(float3 dif, float3 L, float3 N)
{
    return dif * max(dot(N, L), 0.0f) * (1.0f / PI);
}

float4 main(PSInput input) : SV_TARGET
{
    float4 sampleColor = float4(0.8f, 0.8f, 0.8f, 1.0f);
    float3 N = normalize(input.normal);
    float3 L = normalize(input.lightDir);
    float3 lightColor = float3(250.0/255.0,157.0 / 255.0, 27.0 / 255.0);
    float3 dif = calcLam(sampleColor.rgb * lightColor, L, N);

    return float4(dif.xyz, 1.0f);
}

#endif // INCLUDE_LIGHTING_NORMALIZEDLAMBERT_PS_HLSL