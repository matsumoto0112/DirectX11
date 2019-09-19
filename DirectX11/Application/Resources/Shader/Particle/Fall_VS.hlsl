struct FallParticle
{
    float lifeTime : IN_LIFETIME; //!< ¶‘¶ŽžŠÔ
    float3 position : POSITION; //!< À•W
    float3 velocity : IN_VELOCITY; //!< ‘¬“x
    float4 color : COLOR; //!< F
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