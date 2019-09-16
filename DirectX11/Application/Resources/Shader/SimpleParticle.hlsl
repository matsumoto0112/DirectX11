#include "Utility/ShaderDefine.hlsli"

struct GSInput
{
    float4 pos : POSITION;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

[maxvertexcount(6)]
void main(point GSInput input[1], inout TriangleStream<PSInput> output)
{
    float4 pos[4];
    pos[0] = input[0].pos + float4(0.5f, 0.5f, 0.0f, 0.0f);
    pos[1] = input[0].pos + float4(-0.5f, 0.5f, 0.0f, 0.0f);
    pos[2] = input[0].pos + float4(-0.5f, -0.5f, 0.0f, 0.0f);
    pos[3] = input[0].pos + float4(0.5f, -0.5f, 0.0f, 0.0f);

    float4x4 m = mul(mat.world, mat.view);
    m = mul(m, mat.proj);

    PSInput o;
    o.pos = mul(pos[0], m);
    o.uv = float2(0.0f, 0.0f);
    output.Append(o);
    o.pos = mul(pos[1], m);
    o.uv = float2(1.0f, 0.0f);
    output.Append(o);
    o.pos = mul(pos[2], m);
    o.uv = float2(1.0f, 1.0f);
    output.Append(o);
    output.RestartStrip();

    o.pos = mul(pos[0], m);
    o.uv = float2(0.0f, 0.0f);
    output.Append(o);
    o.pos = mul(pos[2], m);
    o.uv = float2(1.0f, 1.0f);
    output.Append(o);
    o.pos = mul(pos[3], m);
    o.uv = float2(0.0f, 1.0f);
    output.Append(o);
    output.RestartStrip();
}