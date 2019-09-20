#include "../Compute/ComputeShaderDefine.hlsli"

#define THREAD_X (32)
#define THREAD_Y (32)
#define THREAD_Z (1)

#define DISPATCH_X (8)
#define DISPATCH_Y (8)
#define DISPATCH_Z (1)

#define RANDOM_MAX 65535

struct FallParticle
{
    float lifeTime; //!< 生存時間
    float3 position; //!< 座標
    float3 velocity; //!< 速度
    float3 scale; //!< 大きさ
    float3 rotate; //<! 回転量
    float3 angular; //!< 回転速度
    float4 color; //!< 色
};

#define LIFETIME_OFFSET (4 * 0)
#define POSITION_OFFSET (4 * 1)
#define VELOCITY_OFFSET (4 * 4)
#define SCALE_OFFSET (4 * 7)
#define ROTATE_OFFSET (4 * 10)
#define ANGULAR_OFFSET (4 * 13)
#define COLOR_OFFSET (4 * 16)
#define PARTICLE_SIZE (4 * 20)

cbuffer GlobalData : register(b0)
{
    float deltaTime; //!< 前フレームからの差分時間
    float gravity; //!< 毎秒かかる重力
    float3 center;
};

StructuredBuffer<float> randomTable : register(t0);
RWByteAddressBuffer particles : register(u0);
RWByteAddressBuffer randomSeed : register(u1);

static const float MaxAlpha = 1.0f;

float getRandom()
{
    uint addr;
    randomSeed.InterlockedAdd(0, 1, addr);
    return randomTable[addr % RANDOM_MAX];
}

float randomRange(float low, float high)
{
    return low + getRandom() * (high - low);
}

float3 getPosition(int index)
{
    return asfloat(particles.Load3(index + POSITION_OFFSET));
}

float3 getVelocity(int index)
{
    return asfloat(particles.Load3(index + VELOCITY_OFFSET));
}

float3 getRotate(int index)
{
    return asfloat(particles.Load3(index + ROTATE_OFFSET));
}

float3 getAngular(int index)
{
    return asfloat(particles.Load3(index + ANGULAR_OFFSET));
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
    float x = randomRange(-1, 1);
    float y = randomRange(-1, 1);
    float z = randomRange(-1, 1);

    return float3(x, y, z) + center;
}

float3 getRandomVelocity()
{
    float x = randomRange(-5.0f, 5.0f);
    float y = randomRange(1.0f, 5.0f);
    float z = randomRange(-5.0f, 5.0f);
    return float3(x, y, z);
}

float3 getRandomScale()
{
    static const float MIN = 0.1f;
    static const float MAX = 1.0f;

    float x = randomRange(MIN, MAX);

    return float3(x, x, x);
}

float4 getRandomColor()
{
    return float4(188.0 / 255.0, 226.0 / 255.0, 232.0 / 255.0, MaxAlpha);
}

void resetParticle(int index)
{
    particles.Store3(index + POSITION_OFFSET, asuint(getRandomPosition()));

    particles.Store(index + LIFETIME_OFFSET, asuint(getRandomLifeTime()));

    particles.Store3(index + VELOCITY_OFFSET, asuint(getRandomVelocity()));

    particles.Store3(index + SCALE_OFFSET, asuint(getRandomScale()));

    particles.Store3(index + ROTATE_OFFSET, asuint(float3(0.0f, 0.0f, 0.0f)));

    particles.Store3(index + ANGULAR_OFFSET, asuint(float3(randomRange(0.0f, 1.0f), randomRange(0.0f, 1.0f), randomRange(0.0f, 1.0f))));

    particles.Store4(index + COLOR_OFFSET, asuint(getRandomColor()));
};


void updateParticle(int index)
{
    //移動処理
    float3 vel = getVelocity(index);
    float3 pos = getPosition(index) + vel * deltaTime;
    particles.Store3(index + POSITION_OFFSET, asuint(pos));

    vel.y -= gravity * deltaTime;
    //地面より下に行ったら速度を反転させ、勢いを減らす
    if (pos.y < -3 && vel.y < 0)
    {
        pos.y = -3;
        vel.y *= -1;
        vel *= 0.8f;
    }
    vel.y = clamp(vel.y, -8.0f, 8.0f);

    particles.Store3(index + VELOCITY_OFFSET, asuint(vel));

    particles.Store3(index + ROTATE_OFFSET, asuint(getRotate(index) + getAngular(index) * deltaTime));

    float life = getLifeTime(index) - deltaTime;
    particles.Store(index + LIFETIME_OFFSET, asuint(life));
    life = max(life, 0);
    //残り1秒を切ったら透明になる
    float t = floor(life) == 0 ? life : 1;
    float alpha = lerp(0.0f, MaxAlpha, t);
    particles.Store(index + COLOR_OFFSET + 4 * 3, asuint(alpha));

};

[numthreads(THREAD_X, THREAD_Y, THREAD_Z)]
void main(const CSInput input)
{
    const uint index = input.dispatch.z * DISPATCH_X * THREAD_X * DISPATCH_Y * THREAD_Y
        + input.dispatch.y * DISPATCH_X * THREAD_X
        + input.dispatch.x;

    const uint addr = index * PARTICLE_SIZE;

    AllMemoryBarrierWithGroupSync();
    if (getLifeTime(addr) > 0)
    {
        updateParticle(addr);
    }
    else
    {
        resetParticle(addr);
    }
}