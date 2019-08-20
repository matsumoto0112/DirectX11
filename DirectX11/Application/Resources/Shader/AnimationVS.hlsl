#include "ShaderDefine.hlsli"

struct vs_input
{
    float4 pos : POSITION;
    float3 nor : NORMAL;
    float2 tex : TEXCOORD0;
    float4 col : COLOR;
    uint4 index : BLENDINDICES0;
    float4 weight : BLENDWEIGHT0;
};

struct ps_input
{
    float4 pos : SV_POSITION;
    float4 nor : NORMAL;
    float2 tex : TEXCOORD0;
    float4 col : COLOR;
};

ps_input main(vs_input input)
{
    ps_input output = (ps_input) 0;

    float lastWeight = 0.0f;
    float4 Pos = 0;
    Pos += mul(input.pos, bones[input.index.x]) * input.weight.x;
    lastWeight += input.weight.x;
    Pos += mul(input.pos, bones[input.index.y]) * input.weight.y;
    lastWeight += input.weight.y;
    Pos += mul(input.pos, bones[input.index.z]) * input.weight.z;
    lastWeight += input.weight.z;
    Pos += mul(input.pos, bones[input.index.w]) * (1.0 - lastWeight);
    output.pos = mul(Pos, mat.world);
    output.pos = mul(output.pos, mat.view);
    output.pos = mul(output.pos, mat.proj);

    float4 Nor = 0;
    Nor += mul(input.nor, (float3x4) bones[input.index.x]) * input.weight.x;
    Nor += mul(input.nor, (float3x4) bones[input.index.y]) * input.weight.y;
    Nor += mul(input.nor, (float3x4) bones[input.index.z]) * input.weight.z;
    Nor += mul(input.nor, (float3x4) bones[input.index.w]) * input.weight.w;
    output.nor = mul(Nor, mat.world);

    output.tex = input.tex;
    output.col = input.col;

    return output;
}