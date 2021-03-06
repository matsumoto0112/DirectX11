#include "ComputeShaderDefine.hlsli"

#define THREAD_X (16)
#define THREAD_Y (16)
#define THREAD_Z (1)

#define DISPATCH_X (8)
#define DISPATCH_Y (8)
#define DISPATCH_Z (1)

struct Particle
{
    float lifeTime; //!< 生存時間
    float3 position; //!< 座標
    float3 velocity; //!< 速度
    float4 color; //!< 色
};

#define LIFETIME_OFFSET (0)
#define POSITION_OFFSET (4 * 1)
#define VELOCITY_OFFSET (4 * 4)
#define COLOR_OFFSET    (4 * 7)
#define SIZEOF_PARTICLE (4 * 11)

cbuffer GlobalData : register(b0)
{
    float deltaTime; //!< 前フレームからの差分時間
    int emit; //!< 生成するか 1なら生成する
};

RWByteAddressBuffer particles : register(u1);

float getLifeTime(int index)
{
    return asfloat(particles.Load(index + LIFETIME_OFFSET));
}

//パーティクルが生存しているか
bool isAlive(int index)
{
    return getLifeTime(index) > 0;
};

float3 getPosition(int index)
{
    return asfloat(particles.Load3(index + POSITION_OFFSET));
}

float3 getVelocity(int index)
{
    return asfloat(particles.Load3(index + VELOCITY_OFFSET));
}

void resetParticle(int index)
{
    float life = getRandom() * 5.0f;
    particles.Store(index + LIFETIME_OFFSET, asuint(life));

    //float px = getRandom() * 10.0f - 5.0f;
    float px = getRandom() * 0.8f;
    float py = getRandom() * 6.0f - 3.0f - 1.5f;;
    float pz = 0.0f;
    particles.Store3(index + POSITION_OFFSET, asuint(float3(px, py, pz)));

    float vx = getRandom() * 2.0f - 1.0f;
    float vy = getRandom() + 1.0f;
    float vz = 0.0f;
    particles.Store3(index + VELOCITY_OFFSET, asuint(float3(vx, vy, vz)));

    //float r = getRandom();
    //float g = getRandom();
    //float b = getRandom();
   
    float r = getRandom() * 0.4f + 0.2f;
    float g = getRandom() * 0.3f + 0.1f;
    float b = 0.0f;
    float a = 0.1f;

    particles.Store4(index + COLOR_OFFSET, asuint(float4(r, g, b, a)));
};


void updateParticle(int index)
{
    particles.Store3(index + POSITION_OFFSET, asuint(getPosition(index) + getVelocity(index) * deltaTime));
    float life = getLifeTime(index) - deltaTime;
    particles.Store(index + LIFETIME_OFFSET, asuint(life));
    if (life <= 0)
    {
        particles.Store(index + COLOR_OFFSET + 12, asuint(0.0f));
    }
};

[numthreads(THREAD_X, THREAD_Y, THREAD_Z)]
void main(const CSInput input)
{
    const uint index = input.dispatch.z * DISPATCH_X * THREAD_X * DISPATCH_Y * THREAD_Y
        + input.dispatch.y * DISPATCH_X * THREAD_X
        + input.dispatch.x;

    const uint addr = index * SIZEOF_PARTICLE;

    if (isAlive(addr))
    {
        updateParticle(addr);
    }
    else if (emit == 1)
    {
        resetParticle(addr);
    }
}