#ifndef PARTICLE_BLACKHOLE_CS_HLSL
#define PARTICLE_BLACKHOLE_CS_HLSL

#include "../../Utility/ComputeShaderDefine.hlsli"
#include "../Util/GPUParticleDefine.hlsli"
#include "../Util/UtilFunc.hlsli"

#define THREAD_X (16)
#define THREAD_Y (4)
#define THREAD_Z (1)

#define DISPATCH_X (1)
#define DISPATCH_Y (8)
#define DISPATCH_Z (1)

struct BlackholeParticle
{
    float3 position; //!< 座標
    float radius; //!< 中心からの半径
    float theta; //!< 角度
    float4 color; //!< 色
};

#define POSITION_OFFSET (4 * 0)
#define RADIUS_OFFSET (4 * 3)
#define THETA_OFFSET    (4 * 4)
#define COLOR_OFFSET (4 * 5)
#define BLACKHOLE_SIZE (4 * 9)

RWByteAddressBuffer particles : register(u1);

float3 getPosition(int index)
{
    return asfloat(particles.Load3(index + POSITION_OFFSET));
}

float getRadius(int index)
{
    return asfloat(particles.Load(index + RADIUS_OFFSET));
}

float getTheta(int index)
{
    return asfloat(particles.Load(index + THETA_OFFSET));
}

void resetParticle(int index)
{
    float radius = getRandom() * 1.0f + 1.0f;
    particles.Store(index + RADIUS_OFFSET, asuint(radius));

    float theta = getRandom() * 360.0f;
    particles.Store(index + THETA_OFFSET, asuint(theta));

    float x, y;
    sincos(theta, y, x);
    particles.Store3(index + POSITION_OFFSET, asuint(float3(x, y, 0.0f)));

    particles.Store4(index + COLOR_OFFSET, asuint(float4(1.0f, 1.0f, 1.0f, 1.0f)));
};


void updateParticle(int index)
{
    float theta = getTheta(index) + deltaTime * getRadius(index) * 0.5f;
    float x, y;
    sincos(theta, y, x);
    x *= getRadius(index);
    y *= getRadius(index);
    particles.Store3(index + POSITION_OFFSET, asuint(float3(x, y, 0.0f)));
    particles.Store(index + THETA_OFFSET, asuint(theta));
};

[numthreads(THREAD_X, THREAD_Y, THREAD_Z)]
void main(const CSInput input)
{
    const uint index = input.dispatch.z * DISPATCH_X * THREAD_X * DISPATCH_Y * THREAD_Y
        + input.dispatch.y * DISPATCH_X * THREAD_X
        + input.dispatch.x;

    const uint addr = index * BLACKHOLE_SIZE;

    //最初のフレームに全部生成する
    //最初は-1が来るようにする
    if (emitIndex >= 0)
    {
        updateParticle(addr);
    }
    else
    {
        resetParticle(addr);
    }
}

#endif // PARTICLE_BLACKHOLE_CS_HLSL