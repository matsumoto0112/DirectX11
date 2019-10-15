#ifndef INCLUDE_PARTICLE_ICEBLOCK_VS_HLSL
#define INCLUDE_PARTICLE_ICEBLOCK_VS_HLSL

struct FallParticle
{
    float lifeTime : IN_LIFETIME; //!< ��������
    float3 position : POSITION; //!< ���W
    float3 velocity : IN_VELOCITY; //!< ���x
    float3 scale : IN_SCALE; //!< �傫��
    float3 rotate : IN_ROTATE; //!< ��]��
    float3 angular : IN_ANGULAR; //!< ��]���x
    float4 color : COLOR; //!< �F
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
