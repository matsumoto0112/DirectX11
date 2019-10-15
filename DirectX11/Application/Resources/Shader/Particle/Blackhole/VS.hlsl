#ifndef INCLUDE_PARTICLE_BLACKHOLE_VS_HLSL
#define INCLUDE_PARTICLE_BLACKHOLE_VS_HLSL

struct BlackholeParticle
{
    float3 position : POSITION;
    float radius : IN_RADIUS;
    float theta : IN_THETA;
    float4 color : COLOR;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

VSOutput main(const BlackholeParticle input)
{
    VSOutput o;
    o.position = float4(input.position, 1.0f);
    o.color = input.color;
    return o;
}

#endif // INCLUDE_PARTICLE_BLACKHOLE_VS_HLSL