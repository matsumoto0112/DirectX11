#ifndef INCLUDE_PARTICLE_FALL_VS_HLSL
#define INCLUDE_PARTICLE_FALL_VS_HLSL

struct FallParticle
{
    float lifeTime : IN_LIFETIME; //!< 生存時間
    float3 position : POSITION; //!< 座標
    float3 velocity : IN_VELOCITY; //!< 速度
    float4 color : COLOR; //!< 色
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

VSOutput main(const FallParticle input)
{
    VSOutput o;
    o.position = float4(input.position, 1.0f);
    o.color = input.color;
    return o;
}

#endif // INCLUDE_PARTICLE_FALL_VS_HLSL