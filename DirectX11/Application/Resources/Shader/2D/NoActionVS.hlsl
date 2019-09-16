struct Particle
{
    float lifeTime : IN_TIME;
    float3 position : POSITION;
    float3 velocity : IN_VELOCITY;
};

float4 main(const Particle input) : SV_POSITION
{
    return float4(input.position, 1.0f);
}