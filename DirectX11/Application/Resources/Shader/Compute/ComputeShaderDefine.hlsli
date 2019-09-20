StructuredBuffer<float> randomTable : register(t0);
RWByteAddressBuffer randomSeed : register(u0);
#define RANDOM_MAX 65535

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

struct CSInput
{
    uint3 groupThread : SV_GroupThreadID;
    uint3 group : SV_GroupID;
    uint groupIndex : SV_GroupIndex;
    uint3 dispatch : SV_DispatchThreadID;
};
 
float GetRandomNumber(float2 texCoord, int Seed)
{
    return frac(sin(dot(texCoord.xy, float2(12.9898, 78.233)) + Seed) * 43758.5453);
}
 