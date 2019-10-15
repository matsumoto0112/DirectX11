#ifndef INCLUDE_PARTICLE_WORMHOLE_VS_HLSL
#define INCLUDE_PARTICLE_WORMHOLE_VS_HLSL

struct Particle
{
    float lifeTime : IN_LIFETIME; //!< ��������
    float speed : IN_SPEED;
    float3 position : POSITION; //!< ���W
    float3 velocity : IN_VELOCITY; //!< �ړ�����
    float4 color : COLOR; //!< �F
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

VSOutput main(const Particle input)
{
    VSOutput o = (VSOutput) 0;
    o.position = float4(input.position, 1.0f);
    o.color = input.color;
    return o;
}

#endif // INCLUDE_PARTICLE_WORMHOLE_VS_HLSL
