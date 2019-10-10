#include "../Utility/ShaderDefine.hlsli"

struct GSInput
{
    float4 pos : SV_POSITION;
    float3 scale : IN_SCALE;
    float4 color : COLOR;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

[maxvertexcount(36)]
void main(point GSInput input[1], inout TriangleStream<PSInput> output)
{
    float4x4 world = mat3D.world;
    world._m30_m31_m32 = input[0].pos.xyz;
    float4x4 scale = float4x4(
        input[0].scale.x, 0.0f, 0.0f, 0.0f,
        0.0f, input[0].scale.y, 0.0f, 0.0f,
        0.0f, 0.0f, input[0].scale.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    float4x4 m = mul(world, scale);
    m = mul(m, mat3D.view);
    m = mul(m, mat3D.proj);

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

    PSInput o;
    o.col = input[0].color;

    uint i;
    [unroll]
    for (i = 1; i <= 36; i++)
    {
        o.pos = mul(vertices[indices[i - 1]], m);
        output.Append(o);
        if (i % 3 == 0)
            output.RestartStrip();
    }
}