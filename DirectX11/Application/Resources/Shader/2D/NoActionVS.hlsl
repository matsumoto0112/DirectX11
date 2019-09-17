struct Particle
{
    float lifeTime : IN_TIME;
    float3 position : POSITION;
    float3 velocity : IN_VELOCITY;
    float4 color : COLOR;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

VSOutput main(const Particle input)
{
    VSOutput o;
    o.position = float4(input.position, 1.0f);
    o.color = input.color;
    return o;
}