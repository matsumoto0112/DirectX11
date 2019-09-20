#include "../Compute/ComputeShaderDefine.hlsli"

#define THREAD_X (16)
#define THREAD_Y (16)
#define THREAD_Z (1)

#define DISPATCH_X (8)
#define DISPATCH_Y (8)
#define DISPATCH_Z (1)

struct FallParticle
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
    float gravity; //!< 毎秒かかる重力
};

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
    static const float minLifeTime = 1.0f;
    static const float maxLifeTime = 5.0f;
    return randomRange(minLifeTime, maxLifeTime);
}

float3 getRandomPosition()
{
    static const float3 MinInitPosition = float3(-5.0f, 3.0f, 0);
    static const float3 MaxInitPosition = float3(5.0f, 3.0f, 0);

    float x = randomRange(MinInitPosition.x, MaxInitPosition.x);
    float y = randomRange(MinInitPosition.y, MaxInitPosition.y);
    float z = randomRange(MinInitPosition.z, MaxInitPosition.z);

    return float3(x, y, z);
}

float3 getRandomVelocity()
{
    float x = randomRange(-1.0f, 1.0f);
    float y = 0.0f;
    float z = 0.0f;
    return float3(x, y, z);
}

float4 getRandomColor()
{
    return float4(188.0 / 255.0, 226.0 / 255.0, 232.0 / 255.0, 0.15f);
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
    float3 vel = getVelocity(index);
    particles.Store3(index + POSITION_OFFSET, asuint(getPosition(index) + vel * deltaTime));
    vel.y -= gravity * deltaTime;

    particles.Store3(index + VELOCITY_OFFSET, asuint(vel));

    particles.Store(index + LIFETIME_OFFSET, asuint(getLifeTime(index) - deltaTime));
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
        resetParticle(addr);
    }
}