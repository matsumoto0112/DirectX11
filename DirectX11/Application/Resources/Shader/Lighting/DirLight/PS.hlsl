#ifndef INCLUDE_LIGHTING_DIRLIGHT_PS_HLSL
#define INCLUDE_LIGHTING_DIRLIGHT_PS_HLSL

#include "../../Utility/ShaderDefine.hlsli"
#include "../../Utility/UtilFunc.hlsli"

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 lightPos = calcLightPos();
    float4 inLightDir = mul(mat3D.world, lightPos);
    float intensity = max(0.3f, saturate(dot(normalize(input.normal), inLightDir.xyz)) * 1.5);

    float4 _Color = float4(1, 0.5f, 0.2f, 1);
    float r = saturate(_Color.r * intensity);
    float g = saturate(_Color.g * intensity);
    float b = saturate(_Color.b * intensity);
    return float4(r, g, b, 1.0f);
}

#endif // INCLUDE_LIGHTING_DIRLIGHT_PS_HLSL