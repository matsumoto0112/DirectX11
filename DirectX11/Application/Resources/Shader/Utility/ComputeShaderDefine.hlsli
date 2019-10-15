#ifndef INCLUDE_UTILITY_COMPUTESHADERDEFINE_HLSLI
#define INCLUDE_UTILITY_COMPUTESHADERDEFINE_HLSLI

struct CSInput
{
    uint3 groupThread : SV_GroupThreadID;
    uint3 group : SV_GroupID;
    uint groupIndex : SV_GroupIndex;
    uint3 dispatch : SV_DispatchThreadID;
};


#endif // INCLUDE_UTILITY_COMPUTESHADERDEFINE_HLSLI
