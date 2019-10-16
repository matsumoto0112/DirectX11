#ifndef INCLUDE_PARTICLE_FIREFLY_CS_HLSL
#define INCLUDE_PARTICLE_FIREFLY_CS_HLSL

#include "../../Utility/ComputeShaderDefine.hlsli"
#include "../Util/GPUParticleDefine.hlsli"
#include "../Util/UtilFunc.hlsli"

#define THREAD_X (32)
#define THREAD_Y (32)
#define THREAD_Z (1)

#define DISPATCH_X (1)
#define DISPATCH_Y (1)
#define DISPATCH_Z (1)

struct Particle
{
    float moveTime; //何秒動いたら 
    float nextRotateTime; //次の移動方向変更秒数
    float angle;
    float3 position; // 現在座標
    float3 scale; //スケール
    float4 color; //色
};

#define MOVETIME_OFFSET (4 * 0)
#define NEXTROTATETIME_OFFSET (4 * 1)
#define ANGLE_OFFSET (4 * 2)
#define POSITION_OFFSET (4 * 3)
#define SCALE_OFFSET (4 * 6)
#define COLOR_OFFSET (4 * 9)
#define PARTICLE_SIZE (4 * 13)

RWByteAddressBuffer particles : register(u1);

float getMoveTime(uint index)
{
    return asfloat(particles.Load(index + MOVETIME_OFFSET));
}

float getNextRotateTime(uint index)
{
    return asfloat(particles.Load(index + NEXTROTATETIME_OFFSET));
}

float getAngle(uint index)
{
    return asfloat(particles.Load(index + ANGLE_OFFSET));
}

float3 getPosition(uint index)
{
    return asfloat(particles.Load3(index + POSITION_OFFSET));
}

float3 getScale(uint index)
{
    return asfloat(particles.Load3(index + SCALE_OFFSET));
}

float3 getRandomPosition()
{
    float x = randomRange(-5, 5);
    float y = randomRange(-5, 5);
    float z = randomRange(-5, 5);
    return float3(x, y, z);
}

float3 getRandomScale()
{
    static const float MIN_SCALE = 0.05f;
    static const float MAX_SCALE = 0.1f;
    float x = randomRange(MIN_SCALE, MAX_SCALE);
    return float3(x, x, x);
}

float4 getRandomColor()
{
    static const float MIN_R = 0.1f;
    static const float MAX_R = 0.3f;
    static const float MIN_G = 0.6f;
    static const float MAX_G = 0.9f;
    static const float MIN_B = 0.1f;
    static const float MAX_B = 0.3f;

    float r = randomRange(MIN_R, MAX_R);
    float g = randomRange(MIN_G, MAX_G);
    float b = randomRange(MIN_B, MAX_B);
    return float4(r, g, b, 0.4f);
}

void storeMoveTime(uint index, float value)
{
    particles.Store(index + MOVETIME_OFFSET, asuint(value));
}

void storeNextRotateTime(uint index, float value)
{
    particles.Store(index + NEXTROTATETIME_OFFSET, asuint(value));
}

void storeAngle(uint index, float value)
{
    particles.Store(index + ANGLE_OFFSET, asuint(value));
}

void storePosition(uint index, float3 value)
{
    particles.Store3(index + POSITION_OFFSET, asuint(value));
}

void resetParticle(uint index)
{
    storeMoveTime(index, 0);
    storeNextRotateTime(index, 0);
    storeAngle(index, radians(randomRange(0, 360)));
    particles.Store3(index + POSITION_OFFSET, asuint(getRandomPosition()));
    particles.Store3(index + SCALE_OFFSET, asuint(getRandomScale()));
    particles.Store4(index + COLOR_OFFSET, asuint(getRandomColor()));
}

void nextMove(uint index)
{
    float angle = getAngle(index);
    angle += radians(randomRange(0, 90.0f));
    storeAngle(index, angle);
    float nextRotate = randomRange(1.0f, 5.0f);
    storeNextRotateTime(index, nextRotate);
    storeMoveTime(index, 0);
}

void updateParticle(uint index)
{
    static const float SPEED = 0.12f;

    if (getMoveTime(index) > getNextRotateTime(index))
    {
        nextMove(index);
    }
    float3 pos = getPosition(index);
    float angle = getAngle(index);
    float x, z;
    sincos(angle, x, z);
    pos += float3(x, z, 0) * SPEED * deltaTime;
    storePosition(index, pos);
    float time = getMoveTime(index);
    time += deltaTime;
    storeMoveTime(index, time);
}

[numthreads(THREAD_X, THREAD_Y, THREAD_Z)]
void main(const CSInput input)
{
    const uint index = input.dispatch.z * DISPATCH_X * THREAD_X * DISPATCH_Y * THREAD_Y
        + input.dispatch.y * DISPATCH_X * THREAD_X
        + input.dispatch.x;

    const uint addr = index * PARTICLE_SIZE;

    if (emitIndex == 0)
    {
        resetParticle(addr);
        return;
    }
    updateParticle(addr);
}

#endif // INCLUDE_PARTICLE_FIREFLY_CS_HLSL