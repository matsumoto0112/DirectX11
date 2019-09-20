#include "../Compute/ComputeShaderDefine.hlsli"

#define THREAD_X (32)
#define THREAD_Y (32)
#define THREAD_Z (1)

#define DISPATCH_X (1)
#define DISPATCH_Y (1)
#define DISPATCH_Z (1)

struct FallParticle
{
    float lifeTime; //!< 生存時間
    float3 position; //!< 座標
    float3 velocity; //!< 速度
    float3 scale; //!< 大きさ
    float4 color; //!< 色
};

#define LIFETIME_OFFSET (4 * 0)
#define POSITION_OFFSET (4 * 1)
#define VELOCITY_OFFSET (4 * 4)
#define SCALE_OFFSET (4 * 7)
#define COLOR_OFFSET (4 * 10)
#define PARTICLE_SIZE (4 * 14)

cbuffer GlobalData : register(b0)
{
    float deltaTime; //!< 前フレームからの差分時間
    float3 pos;
    float3 vel;
    uint emit;
    float4 col;
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
    static const float minLifeTime = 5.0f;
    static const float maxLifeTime = 15.0f;
    return randomRange(minLifeTime, maxLifeTime);
}

float3 getRandomPosition()
{
    static const float Variation = 1.0f;
    const float x = randomRange(-Variation, Variation);
    const float y = randomRange(-Variation, Variation);
    const float z = randomRange(-Variation, Variation);
    return float3(x, y, z) + pos;
}

float3 getRandomVelocity()
{
    float3 res = vel;
    float y = randomRange(-1.0f, 1.0f);
    res.y += y;
    return res;
}

float3 getRandomScale()
{
    static const float MIN = 1.0f;
    static const float MAX = 1.0f;

    float x = randomRange(MIN, MAX);

    return float3(x, x, x);
}

float4 getRandomColor()
{
    return col;
}

void resetParticle(int index)
{
    particles.Store3(index + POSITION_OFFSET, asuint(getRandomPosition()));

    particles.Store(index + LIFETIME_OFFSET, asuint(getRandomLifeTime()));

    particles.Store3(index + VELOCITY_OFFSET, asuint(getRandomVelocity()));

    particles.Store3(index + SCALE_OFFSET, asuint(getRandomScale()));

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
        if (emit == input.groupIndex)
            resetParticle(addr);
        else
        {
            particles.Store(addr + COLOR_OFFSET + 4 * 3, asuint(0.0f));
        }
    }
}