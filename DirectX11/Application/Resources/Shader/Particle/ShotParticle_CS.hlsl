#include "../Compute/ComputeShaderDefine.hlsli"
#include "../Utility/Util.hlsli"

#define THREAD_X (16)
#define THREAD_Y (16)
#define THREAD_Z (1)

#define DISPATCH_X (1)
#define DISPATCH_Y (1)
#define DISPATCH_Z (1)

struct Particle
{
    float lifeTime; //!< 生存時間
    float3 position; //!< 座標
    float3 velocity; //!< 速度
    float4 color; //!< 色
};

#define LIFETIME_OFFSET (4 * 0)
#define POSITION_OFFSET (4 * 1)
#define VELOCITY_OFFSET (4 * 4)
#define COLOR_OFFSET (4 * 7)
#define PARTICLE_SIZE (4 * 11)

cbuffer GlobalData : register(b0)
{
    float deltaTime; //!< 前フレームからの差分時間
};

cbuffer OnceShotData : register(b1)
{
    uint emitIndex;
    float3 pos;
}

RWByteAddressBuffer particles : register(u1);

float3 getPosition(int index)
{
    return asfloat(particles.Load3(index + POSITION_OFFSET));
}

float3 getVelocity(int index)
{
    return asfloat(particles.Load3(index + VELOCITY_OFFSET));
}

float getLifeTime(int index)
{
    return asfloat(particles.Load(index + LIFETIME_OFFSET));
}

float getRandomLifeTime()
{
    static const float minLifeTime = 0.25f;
    static const float maxLifeTime = 0.5f;
    return randomRange(minLifeTime, maxLifeTime);
}

float3 getRandomPosition()
{
    static const float Variation = 0.25f;
    const float x = randomRange(-Variation, Variation);
    const float y = randomRange(-Variation, Variation);
    const float z = randomRange(-Variation, Variation);
    return float3(x, y, z) + pos;
}

float3 getRandomVelocity()
{
    const float y = randomRange(5.0f, 20.0f);
    return float3(0, y, 0);
}

float4 getRandomColor()
{
    static const float4 minColor = float4(convertColorFromInt3(int3(235, 164, 10)), 0.5);
    static const float4 maxColor = float4(convertColorFromInt3(int3(245, 255, 66)), 0.8);
    //static const float4 minColor = float4(convertColorFromInt3(int3(0, 0, 0)), 1.0);
    //static const float4 maxColor = float4(convertColorFromInt3(int3(255, 255, 255)), 1.0);
    const float r = randomRange(minColor.r, maxColor.r);
    const float g = randomRange(minColor.g, maxColor.g);
    const float b = randomRange(minColor.b, maxColor.b);
    const float a = randomRange(minColor.a, maxColor.a);
    return float4(r, g, b, a);
}

void resetParticle(int index)
{
    particles.Store3(index + POSITION_OFFSET, asuint(getRandomPosition()));

    particles.Store(index + LIFETIME_OFFSET, asuint(getRandomLifeTime()));

    particles.Store3(index + VELOCITY_OFFSET, asuint(getRandomVelocity()));

    particles.Store4(index + COLOR_OFFSET, asuint(getRandomColor()));
};

void updateParticle(int index)
{
    //移動処理
    float3 vel = getVelocity(index);
    float3 pos = getPosition(index) + vel * deltaTime;
    particles.Store3(index + POSITION_OFFSET, asuint(pos));

    float life = getLifeTime(index) - deltaTime;
    particles.Store(index + LIFETIME_OFFSET, asuint(life));
};

[numthreads(THREAD_X, THREAD_Y, THREAD_Z)]
void main(const CSInput input)
{
    const uint index = input.dispatch.z * DISPATCH_X * THREAD_X * DISPATCH_Y * THREAD_Y
        + input.dispatch.y * DISPATCH_X * THREAD_X
        + input.dispatch.x;

    const uint addr = index * PARTICLE_SIZE;

    if (getLifeTime(addr) > 0)
    {
        updateParticle(addr);
    }
    else
    {
        if (emitIndex == input.groupIndex)
            resetParticle(addr);
        else
            particles.Store(addr + COLOR_OFFSET + 4 * 3, asuint(0.0f));
    }
}