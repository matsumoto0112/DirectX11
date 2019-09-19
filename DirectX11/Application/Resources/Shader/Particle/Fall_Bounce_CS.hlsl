#include "../Compute/ComputeShaderDefine.hlsli"

#define THREAD_X (16)
#define THREAD_Y (16)
#define THREAD_Z (1)

#define DISPATCH_X (8)
#define DISPATCH_Y (8)
#define DISPATCH_Z (1)

#define RANDOM_MAX 65535

struct FallParticle
{
    float lifeTime; //!< ��������
    float3 position; //!< ���W
    float3 velocity; //!< ���x
    float3 scale; //!< �傫��
    float4 color; //!< �F
};

#define LIFETIME_OFFSET (4 * 0)
#define POSITION_OFFSET (4 * 1)
#define VELOCITY_OFFSET (4 * 4)
#define SCALE_OFFSET (4 * 7)
#define COLOR_OFFSET (4 * 10)
#define PARTICLE_SIZE (4 * 14)

cbuffer GlobalData : register(b0)
{
    float deltaTime; //!< �O�t���[������̍�������
    float gravity; //!< ���b������d��
};

StructuredBuffer<float> randomTable : register(t0);
RWByteAddressBuffer particles : register(u0);
RWByteAddressBuffer randomSeed : register(u1);
groupshared int emitNum = 0;

static const float MaxAlpha = 0.3f;

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

float getLifeTime(int index)
{
    return asfloat(particles.Load(index + LIFETIME_OFFSET));
}

float getRandomLifeTime()
{
    static const float minLifeTime = 3.0f;
    static const float maxLifeTime = 10.0f;
    return randomRange(minLifeTime, maxLifeTime);
}

float3 getRandomPosition()
{
    static const float3 MinInitPosition = float3(-5.0f, 3.0f, -5.0f);
    static const float3 MaxInitPosition = float3(5.0f, 3.0f, 5.0f);

    //float x = randomRange(MinInitPosition.x, MaxInitPosition.x);
    //float y = randomRange(MinInitPosition.y, MaxInitPosition.y);
    //float z = randomRange(MinInitPosition.z, MaxInitPosition.z);
    float x = randomRange(0, 0);
    float y = randomRange(3, 3);
    float z = randomRange(0, 0);

    return float3(x, y, z);
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

    particles.Store4(index + COLOR_OFFSET, asuint(getRandomColor()));
};


void updateParticle(int index)
{
    //�ړ�����
    float3 vel = getVelocity(index);
    float3 pos = getPosition(index) + vel * deltaTime;
    particles.Store3(index + POSITION_OFFSET, asuint(pos));
    vel.y -= gravity * deltaTime;
    //�n�ʂ�艺�ɍs�����瑬�x�𔽓]�����A���������炷
    if (pos.y < -3 && vel.y < 0)
    {
        vel.y *= -1;
        vel *= 0.8f;
    }
    vel.y = clamp(vel.y, -8.0f, 8.0f);

    particles.Store3(index + VELOCITY_OFFSET, asuint(vel));

    //�������ԊǗ�
    float life = getLifeTime(index);
    life = clamp(life - deltaTime, 0, life);
    particles.Store(index + LIFETIME_OFFSET, asuint(life));

    //�c��1�b��؂����瓧���ɂȂ�
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
        if (emitNum < 1)
        {
            resetParticle(addr);
            emitNum++;
        }
    }
}