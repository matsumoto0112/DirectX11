#include "Utility/ShaderDefine.hlsli"

struct GSInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 col : COLOR;
};

[maxvertexcount(6)]
void main(point GSInput input[1], inout TriangleStream<PSInput> output)
{
    float4 pos[4];
    pos[0] = float4(0.5f, 0.5f, 0.0f, 1.0f);
    pos[1] = float4(-0.5f, 0.5f, 0.0f, 1.0f);
    pos[2] = float4(-0.5f, -0.5f, 0.0f, 1.0f);
    pos[3] = float4(0.5f, -0.5f, 0.0f, 1.0f);

    float4x4 world = mat.world;
    world._m30_m31_m32 = input[0].pos.xyz;
    float4x4 m = mul(world, mat.view);
    m = mul(m, mat.proj);

    PSInput o;
    o.col = input[0].color;
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