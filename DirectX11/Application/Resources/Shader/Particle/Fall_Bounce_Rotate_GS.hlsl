#include "../Utility/ShaderDefine.hlsli"

struct GSInput
{
    float4 pos : SV_POSITION;
    float3 scale : IN_SCALE;
    float3 rotate : IN_ROTATE;
    float4 color : COLOR;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

float3 rotate(float4 pos, float3 rotate)
{
    float3 p = (float3) 0;
    p += pos.xyz;
    float3 a = normalize(rotate);
    float angle = length(rotate);
    if (abs(angle) >= 0.001)
    {
        float s = sin(angle);
        float c = cos(angle);
        float r = 1.0 - c;
        float3x3 m = float3x3(
        a.x * a.x * r + c,
        a.y * a.x * r + a.z * s,
        a.z * a.x * r - a.y * s,
        a.x * a.y * r - a.z * s,
        a.y * a.y * r + c,
        a.z * a.y * r + a.x * s,
        a.x * a.z * r + a.y * s,
        a.y * a.z * r - a.x * s,
        a.z * a.z * r + c
        );
        p = mul(m, p);
    }
    return p;
}

[maxvertexcount(36)]
void main(point GSInput input[1], inout TriangleStream<PSInput> output)
{
    float4x4 m = WORLD_VIEW_PROJECTION_3D();

    float4 vertices[] =
    {
        float4(-0.5f, 0.5f, -0.5f, 1.0f),
        float4(0.5f, 0.5f, -0.5f, 1.0f),
        float4(0.5f, -0.5f, -0.5f, 1.0f),
        float4(-0.5f, -0.5f, -0.5f, 1.0f),
        float4(-0.5f, 0.5f, 0.5f, 1.0f),
        float4(0.5f, 0.5f, 0.5f, 1.0f),
        float4(0.5f, -0.5f, 0.5f, 1.0f),
        float4(-0.5f, -0.5f, 0.5f, 1.0f)
    };

    uint indices[36] =
    {
        0, 1, 2,
        0, 2, 3,
        4, 0, 3,
        4, 3, 7,
        5, 4, 7,
        5, 7, 6,
        1, 5, 6,
        1, 6, 2,
        3, 2, 6,
        3, 6, 7,
        4, 5, 1,
        4, 1, 0,
    };

    PSInput o = (PSInput) 0;
    o.col = input[0].color;

    uint i;
    [unroll]
    for (i = 1; i <= 36; i++)
    {
        o.pos = vertices[indices[i - 1]];
        o.pos.xyz *= input[0].scale;
        o.pos.xyz = rotate(o.pos, input[0].rotate);
        o.pos += input[0].pos;
        o.pos = mul(o.pos, m);
        output.Append(o);
        if (i % 3 == 0)
            output.RestartStrip();
    }
}