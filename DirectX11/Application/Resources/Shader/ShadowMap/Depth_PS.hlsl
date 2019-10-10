
Texture2D<float> tex : register(t0);
SamplerState samplerState : register(s0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float dep = tex.Sample(samplerState, input.uv);
    return float4(dep, dep, dep, 1.0f);
}