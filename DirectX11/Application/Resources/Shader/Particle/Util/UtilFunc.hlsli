#ifndef INCLUDE_PARTICLE_UTILFUNC_HLSLI
#define INCLUDE_PARTICLE_UTILFUNC_HLSLI

#include "GPUParticleDefine.hlsli"

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
 
float GetRandomNumber(float2 texCoord, int Seed)
{
    return frac(sin(dot(texCoord.xy, float2(12.9898, 78.233)) + Seed) * 43758.5453);
}

#endif // INCLUDE_PARTICLE_UTILFUNC_HLSLI
