#ifndef INCLUDE_PARTICLE_ICEBLOCK_VS_HLSL
#define INCLUDE_PARTICLE_ICEBLOCK_VS_HLSL

struct FallParticle
{
    float lifeTime : IN_LIFETIME; //!< ¶‘¶ŽžŠÔ
    float3 position : POSITION; //!< À•W
    float3 velocity : IN_VELOCITY; //!< ‘¬“x
    float3 scale : IN_SCALE; //!< ‘å‚«‚³
    float3 rotate : IN_ROTATE; //!< ‰ñ“]—Ê
    float3 angular : IN_ANGULAR; //!< ‰ñ“]‘¬“x
    float4 color : COLOR; //!< F
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 scale : IN_SCALE;
    float3 rotate : IN_ROTATE;
    float4 color : COLOR0;
};

VSOutput main(const FallParticle input)
{
    VSOutput o = (VSOutput)0;
    o.position = float4(input.position, 1.0f);
    o.scale = input.scale;
    o.rotate = input.rotate;
    o.color = input.color;
    return o;
}

#endif // INCLUDE_PARTICLE_ICEBLOCK_VS_HLSL
