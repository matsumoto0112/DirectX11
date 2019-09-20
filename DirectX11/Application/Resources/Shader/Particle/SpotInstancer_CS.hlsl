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
    float speed; //!< 移動速度
    float3 position; //!< 座標
    float3 velocity; //!< 移動量
    float4 color; //!< 色
};

#define LIFETIME_OFFSET (4 * 0)
#define SPEED_OFFSET (4 * 1)
#define POSITION_OFFSET (4 * 2)
#define VELOCITY_OFFSET (4 * 5)
#define COLOR_OFFSET (4 * 8)
#define PARTICLE_SIZE (4 * 12)

cbuffer GlobalData : register(b0)
{
    float deltaTime; //!< 前フレームからの差分時間
};

cbuffer EmitParameter : register(b1)
{
    uint emitTargetIndex;
    float3 spot; //!< 生成場所
    float3 center;
};

RWByteAddressBuffer particles : register(u1);

float3 getPosition(int index)
{
    return asfloat(particles.Load3(index + POSITION_OFFSET));
}

float getSpeed(int index)
{
    return asfloat(particles.Load(index + SPEED_OFFSET));
}

float3 getVelocity(int index)
{
    return asfloat(particles.Load3(index + VELOCITY_OFFSET));
}

float getLifeTime(int index)
{
    return asfloat(particles.Load(index + LIFETIME_OFFSET));
}

float4 getRandomColor()
{
    float r = getRandom();
    float g = getRandom();
    float b = getRandom();
    return float4(r, g, b, 0.2f);
}

void resetParticle(int index)
{
    float life = randomRange(2.0f, 5.0f);
    particles.Store(index + LIFETIME_OFFSET, asuint(life));
    float3 vel = center - spot;
    particles.Store3(index + VELOCITY_OFFSET, asuint(normalize(vel)));
    particles.Store3(index + POSITION_OFFSET, asuint(spot));

    float speed = length(vel) / (life - 1);
    particles.Store(index + SPEED_OFFSET, asuint(speed));


    particles.Store4(index + COLOR_OFFSET, asuint(getRandomColor()));
};

void updateParticle(int index)
{
    particles.Store3(index + POSITION_OFFSET, asuint(getPosition(index) + getVelocity(index) * getSpeed(index) * deltaTime));
    float life = getLifeTime(index) - deltaTime;
    particles.Store(index + LIFETIME_OFFSET, asuint(life));
    if (life <= 0.0f)
        particles.Store(index + COLOR_OFFSET + 4 * 3, asuint(0.0f));
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
        if (input.groupIndex == emitTargetIndex)
            resetParticle(addr);
    }
}