#include "ComputeShaderDefine.hlsli"

#define SIZE_X 16
#define SIZE_Y 16
#define SIZE_Z 1

#define DISPATCH_X 4
#define DISPATCH_Y 1
#define DISPATCH_Z 1

struct Particle
{
    float lifeTime;
    float3 position;
    float3 velocity;
};

#define SIZEOF_FLOAT (4)
#define LIFETIME_OFFSET (0)
#define POSITION_OFFSET (SIZEOF_FLOAT * 1)
#define VELOCITY_OFFSET (SIZEOF_FLOAT * 4)
#define PARTICLE_SIZE (SIZEOF_FLOAT * 7)

cbuffer GlobalData : register(b0)
{
    int seed;
    float deltaTime;
};

RWByteAddressBuffer output0 : register(u0);

bool isAlive(int index)
{
    return asfloat(output0.Load(index + LIFETIME_OFFSET)) > 0;
}

float getTime(int index)
{
    return asfloat(output0.Load(index + LIFETIME_OFFSET));
}

float3 getPosition(int index)
{
    return asfloat(output0.Load3(index + POSITION_OFFSET));
}

float3 getVelocity(int index)
{
    return asfloat(output0.Load3(index + VELOCITY_OFFSET));
}

void resetParticle(int index)
{
    int s = seed * index;
    static const float2 tex = float2(128, 128);
    output0.Store(index + LIFETIME_OFFSET, asuint(GetRandomNumber(tex * 10.0f, ++s)));
    output0.Store3(index + POSITION_OFFSET, asuint(float3(GetRandomNumber(tex, ++s) * 2.0f - 1.0f, 0, GetRandomNumber(tex, ++s) * 5.0f)));
    output0.Store3(index + VELOCITY_OFFSET, asuint(float3(GetRandomNumber(tex, ++s) * 6.0f - 3.0f, 1.0f, 0.0f)));
}

void updateParticle(int index)
{
    output0.Store3(index + POSITION_OFFSET, asuint(getPosition(index) + getVelocity(index) * deltaTime));
    output0.Store(index + LIFETIME_OFFSET, asuint(getTime(index) - deltaTime));
}

[numthreads(SIZE_X, SIZE_Y, SIZE_Z)]
void main(const CSInput input)
{
    uint x = input.dispatch.x;
    uint y = input.dispatch.y;
    uint z = input.dispatch.z;

    //const uint index = input.dispatch.z * SIZE_X * SIZE_Y + input.dispatch.y * SIZE_X + input.dispatch.x;
    const uint index = z * DISPATCH_X * SIZE_X * DISPATCH_Y * SIZE_Y + y * DISPATCH_X * SIZE_X + x;
    const uint address = index * PARTICLE_SIZE;
    //パーティクル生存中
    if (isAlive(address))
    {
        updateParticle(address);
    }
    else
    {
        resetParticle(address);
    }
}