#include "ComputeShaderDefine.hlsli"

#define SIZE_X 256

static const float3 InitPosition = float3(0.0f, 0.0f, 0.0f);
static const float InitLifeTime = 10.0f;
static const float EmitInterval = 1.0f;

struct Particle
{
    bool alive;
    float lifeTime;
    float3 position;
    float3 velocity;
};

cbuffer GlobalData : register(b0)
{
    int seed;
    float deltaTime;
};

RWStructuredBuffer<Particle> output0 : register(u0);

void resetParticle(int index)
{
    output0[index].alive = true;
    output0[index].lifeTime = InitLifeTime;
    output0[index].position = InitPosition;
    float x = GetRandomNumber(float2(index / 256, index / 256), seed);
    float3 vel = float3(x, 1.0f / 60.0f, 0.0f);
    output0[index].velocity = vel;
}

void updateParticle(int index)
{
    output0[index].position += output0[index].velocity * deltaTime;
    output0[index].lifeTime -= deltaTime;
    if (output0[index].lifeTime <= 0.0f)
    {
        output0[index].alive = false;
    }
}

[numthreads(SIZE_X, 1, 1)]
 void main(const CSInput input)
{
    int index = input.dispatch.x;

    //パーティクル生存中
    if (output0[index].alive)
    {
        updateParticle(index);
    }
}