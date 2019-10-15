#ifndef INCLUDE_PARTICLE_OUTPUT_COLOR_PS_HLSL
#define INCLUDE_PARTICLE_OUTPUT_COLOR_PS_HLSL

struct PSInput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
};

float4 main(const PSInput input) : SV_TARGET
{
    return input.col;
}

#endif // INCLUDE_PARTICLE_OUTPUT_COLOR_PS_HLSL
