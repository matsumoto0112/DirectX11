#include "ShaderDefine.hlsli"

Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);
Texture2D tex2 : register(t2);
Texture2D tex3 : register(t3);
SamplerState samLinear : register(s0);

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

float4 main(PS_IN IN) : SV_TARGET
{
    //”wŒi•`‰æ
    float4 result = tex0.Sample(samLinear, IN.Tex);
    float a = result.a;
    //‚»‚Ìã‚É•`‰æ‚·‚é‰æ‘œ
    float4 color = tex1.Sample(samLinear, IN.Tex);
    result = result + (color - result) * color.a * saturate(cameraNum - 1);

    color = tex2.Sample(samLinear, IN.Tex);
    result = result + (color - result) * color.a * saturate(cameraNum - 2);

    color = tex3.Sample(samLinear, IN.Tex);
    result = result + (color - result) * color.a * saturate(cameraNum - 3);

    result.a = a;
    return result;
}