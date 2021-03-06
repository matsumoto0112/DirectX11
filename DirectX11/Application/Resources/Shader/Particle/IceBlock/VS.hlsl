#ifndef INCLUDE_PARTICLE_ICEBLOCK_VS_HLSL
#define INCLUDE_PARTICLE_ICEBLOCK_VS_HLSL

struct FallParticle
{
    float lifeTime : IN_LIFETIME; //!< 生存時間
    float3 position : POSITION; //!< 座標
    float3 velocity : IN_VELOCITY; //!< 速度
    float3 scale : IN_SCALE; //!< 大きさ
    float3 rotate : IN_ROTATE; //!< 回転量
    float3 angular : IN_ANGULAR; //!< 回転速度
    float4 color : COLOR; //!< 色
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
